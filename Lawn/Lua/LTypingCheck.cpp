#include "LLawnLib.h"
#include "../../Lawn/System/TypingCheck.h"

using namespace Sexy;

void open_typecheck(sol::state_view lua) {
    sol::table sexy;
    if (lua["Sexy"].valid() && lua["Sexy"].get_type() == sol::type::table) {
        sexy = lua["Sexy"];
    } else {
        sexy = lua.create_table();
        lua["Sexy"] = sexy;
    }

    sexy.new_usertype<TypingCheck>("TypingCheck",
        sol::constructors<
            TypingCheck(),
            TypingCheck(const std::string&)
        >(),

        "SetPhrase", &TypingCheck::SetPhrase,
        "AddKeyCode", &TypingCheck::AddKeyCode,
        "AddChar", &TypingCheck::AddChar,
        "Check", sol::overload(
            static_cast<bool (TypingCheck::*)()>(&TypingCheck::Check),
            [](TypingCheck& self, int keycode) {
                return self.Check(static_cast<Sexy::KeyCode>(keycode));
            }
        )
    );
}