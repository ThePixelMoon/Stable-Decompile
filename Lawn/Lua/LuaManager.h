#pragma once

#include "../../SexyAppFramework/Common.h"
#include "sol.hpp"

class LuaManager {
public:
	LuaManager();
	virtual ~LuaManager();

	virtual bool LoadFiles();

private:
	sol::state lua;
};

namespace Hook {
    extern sol::table gHookTable;
    void Init(sol::state_view lua);

    template<typename... Args>
    void Call(const std::string& name, Args&&... args) {
        sol::function f = gHookTable[name];
        if (f.valid()) {
            f(std::forward<Args>(args)...);
        }
    }
}