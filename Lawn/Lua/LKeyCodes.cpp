#include "LLawnLib.h"
#include "../../SexyAppFramework/KeyCodes.h"

using namespace Sexy;

void open_keycodes(sol::state_view lua) {
    sol::table sexy;
    if (lua["Sexy"].valid() && lua["Sexy"].get_type() == sol::type::table) {
        sexy = lua["Sexy"];
    } else {
        sexy = lua.create_table();
        lua["Sexy"] = sexy;
    }

    sol::table keycode = lua.create_table();
    keycode["UNKNOWN"]     = KEYCODE_UNKNOWN;
    keycode["RETURN"]      = KEYCODE_RETURN;
    keycode["BACK"]        = KEYCODE_BACK;
    keycode["TAB"]         = KEYCODE_TAB;
    keycode["SPACE"]       = KEYCODE_SPACE;
    keycode["ESCAPE"]      = KEYCODE_ESCAPE;
    keycode["LEFT"]        = KEYCODE_LEFT;
    keycode["RIGHT"]       = KEYCODE_RIGHT;
    keycode["UP"]          = KEYCODE_UP;
    keycode["DOWN"]        = KEYCODE_DOWN;
    keycode["SHIFT"]       = KEYCODE_SHIFT;
    keycode["CONTROL"]     = KEYCODE_CONTROL;
    keycode["ALT"]         = KEYCODE_MENU;
    keycode["DELETE"]      = KEYCODE_DELETE;
    keycode["INSERT"]      = KEYCODE_INSERT;
    keycode["HOME"]        = KEYCODE_HOME;
    keycode["END"]         = KEYCODE_END;
    keycode["PAGEUP"]      = KEYCODE_PRIOR;
    keycode["PAGEDOWN"]    = KEYCODE_NEXT;

    // F1–F12
    for (int i = 1; i <= 12; ++i) {
        keycode["F" + std::to_string(i)] = KEYCODE_F1 + (i - 1);
    }

    sexy["KeyCode"] = keycode;

    sexy.set_function("GetKeyCodeFromName", &GetKeyCodeFromName);
    sexy.set_function("GetKeyNameFromCode", &GetKeyNameFromCode);
}