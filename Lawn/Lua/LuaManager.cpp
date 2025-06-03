#include "LuaManager.h"
#include "LLawnLib.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../PakLib/PakInterface.h"

LuaManager::LuaManager() {
	lua.open_libraries(
		sol::lib::base,
		sol::lib::package,
		sol::lib::coroutine,
		sol::lib::string,
		sol::lib::table,
		sol::lib::math,
		sol::lib::io,
		sol::lib::os,
		sol::lib::debug,
		sol::lib::bit32,
		sol::lib::ffi
	);
	lawn_openlibs(lua);

	// replace print
	lua["print"] = [](sol::variadic_args va) {
        std::string combined;
        bool first = true;
        for (auto v : va) {
            if (!first)
                combined += "\t";
            first = false;

            if (v.is<std::string>()) {
                combined += v.as<std::string>();
            } else if (v.is<bool>()) {
                combined += (v.as<bool>() ? "true" : "false");
            } else if (v.is<double>()) {
                combined += std::to_string(v.as<double>());
            } else if (v.is<int>()) {
                combined += std::to_string(v.as<int>());
            } else {
                combined += "<non-printable>";
            }
        }
        TodTraceAndLog(combined.c_str());
    };
}

bool LuaManager::LoadFiles() {
	WIN32_FIND_DATA findData;
	HANDLE hFind = p_FindFirstFile("lua\\*.lua", &findData);

	if (hFind == INVALID_HANDLE_VALUE) {
		TodTraceAndLog("no Lua scripts found in lua\\\n");
		return false;
	}

	do {
		SexyString filePath = _S("lua\\") + SexyString(findData.cFileName);

		PFILE* file = p_fopen(filePath.c_str(), "r");
		if (!file) {
			TodTraceAndLog("failed to open Lua file: %s\n", filePath.c_str());
			continue;
		}

		p_fseek(file, 0, SEEK_END);
		long size = p_ftell(file);
		p_fseek(file, 0, SEEK_SET);

		SexyString script(size, '\0');
		p_fread(&script[0], 1, size, file);
		p_fclose(file);

		try {
			lua.script(script);
		} catch (const sol::error& e) {
			TodTraceAndLog("Lua error: %s\n", e.what());
		}

	} while (p_FindNextFile(hFind, &findData));
	p_FindClose(hFind);
	return true;
}

LuaManager::~LuaManager() {
}

namespace Hook {
    sol::table gHookTable;

    void Init(sol::state_view lua) {
        if (!lua["Hook"].valid()) {
            lua["Hook"] = lua.create_table();
        }

        gHookTable = lua["Hook"];

        gHookTable["new"] = [](const std::string& name, sol::function func) {
            gHookTable[name] = func;
        };
    }
}