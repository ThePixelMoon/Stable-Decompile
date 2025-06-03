#include "LLawnLib.h"
#include "../../Sexy.TodLib/TodDebug.h"

void open_toddebug(sol::state_view lua) {
    sol::table tod;
    if (lua["tod"].valid() && lua["tod"].get_type() == sol::type::table) {
        tod = lua["tod"];
    } else {
        tod = lua.create_table();
        lua["tod"] = tod;
    }

    tod.set("Log", [](const std::string& msg) { TodLog("%s", msg.c_str()); });
    tod.set("LogString", TodLogString);
    tod.set("Trace", [](const std::string& msg) { TodTrace("%s", msg.c_str()); });
    tod.set("TraceMemory", TodTraceMemory);
    tod.set("TraceAndLog", [](const std::string& msg) { TodTraceAndLog("%s", msg.c_str()); });
    tod.set("TraceWithoutSpamming", [](const std::string& msg) { TodTraceWithoutSpamming("%s", msg.c_str()); });
    tod.set("AssertFailed", [](const std::string& cond, const std::string& file, int line, const std::string& msg) {
        TodAssertFailed(cond.c_str(), file.c_str(), line, msg.c_str());
    });
    tod.set("ErrorMessageBox", [](const std::string& m, const std::string& t) { TodErrorMessageBox(m.c_str(), t.c_str()); });
    tod.set("Malloc", [](int size) { return TodMalloc(size); });
    tod.set("Free", TodFree);
    tod.set("AssertInitForApp", TodAssertInitForApp);
}
