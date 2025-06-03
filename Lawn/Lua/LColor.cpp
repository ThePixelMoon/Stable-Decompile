#include "LLawnLib.h"
#include "../../SexyAppFramework/Color.h"

using namespace Sexy;

void open_color(sol::state_view lua) {
    sol::table sexy;
    if (lua["Sexy"].valid() && lua["Sexy"].get_type() == sol::type::table) {
        sexy = lua["Sexy"];
    } else {
        sexy = lua.create_table();
        lua["Sexy"] = sexy;
    }

    sexy.new_usertype<Sexy::Color>("Color",
        sol::constructors<
            Sexy::Color(), 
            Sexy::Color(int), 
            Sexy::Color(int, int), 
            Sexy::Color(int, int, int), 
            Sexy::Color(int, int, int, int)
        >(),

        "GetRed", &Sexy::Color::GetRed,
        "GetGreen", &Sexy::Color::GetGreen,
        "GetBlue", &Sexy::Color::GetBlue,
        "GetAlpha", &Sexy::Color::GetAlpha,
        "ToInt", &Sexy::Color::ToInt,

        "mRed", &Sexy::Color::mRed,
        "mGreen", &Sexy::Color::mGreen,
        "mBlue", &Sexy::Color::mBlue,
        "mAlpha", &Sexy::Color::mAlpha
    );

    sexy["Color"]["Black"] = Sexy::Color::Black;
    sexy["Color"]["White"] = Sexy::Color::White;
}