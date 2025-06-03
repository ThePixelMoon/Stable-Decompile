#include "LLawnLib.h"
#include "../../SexyAppFramework/Rect.h"

using namespace Sexy;

void open_rect(sol::state_view lua) {
    sol::table sexy;
    if (lua["Sexy"].valid() && lua["Sexy"].get_type() == sol::type::table) {
        sexy = lua["Sexy"];
    } else {
        sexy = lua.create_table();
        lua["Sexy"] = sexy;
    }

    sexy.new_usertype<Sexy::Rect>(
        "Rect",
        sol::constructors<
            Sexy::Rect(),
            Sexy::Rect(int, int, int, int),
            Sexy::Rect(const Sexy::Rect&)
        >(),
        "mX", &Sexy::Rect::mX,
        "mY", &Sexy::Rect::mY,
        "mWidth", &Sexy::Rect::mWidth,
        "mHeight", &Sexy::Rect::mHeight,

        "Intersects", &Sexy::Rect::Intersects,
        "Intersection", &Sexy::Rect::Intersection,
        "Union", static_cast<Sexy::Rect (Sexy::Rect::*)(const Sexy::Rect&)>(&Sexy::Rect::Union),
        "Contains", sol::overload(
            static_cast<bool (Sexy::Rect::*)(int, int) const>(&Sexy::Rect::Contains),
            static_cast<bool (Sexy::Rect::*)(const Sexy::TPoint<int>&) const>(&Sexy::Rect::Contains)
        ),
        "Offset", sol::overload(
            static_cast<void (Sexy::Rect::*)(int, int)>(&Sexy::Rect::Offset),
            static_cast<void (Sexy::Rect::*)(const Sexy::TPoint<int>&)>(&Sexy::Rect::Offset)
        ),
        "Inflate", &Sexy::Rect::Inflate,
        sol::meta_function::to_string, [](const Sexy::Rect& r) {
            return "Rect(" + std::to_string(r.mX) + "," + std::to_string(r.mY) + "," +
                   std::to_string(r.mWidth) + "," + std::to_string(r.mHeight) + ")";
        },
        sol::meta_function::equal_to, &Sexy::Rect::operator==
    );

    sexy.new_usertype<Sexy::FRect>(
        "FRect",
        sol::constructors<
            Sexy::FRect(),
            Sexy::FRect(double, double, double, double),
            Sexy::FRect(const Sexy::FRect&)
        >(),
        "mX", &Sexy::FRect::mX,
        "mY", &Sexy::FRect::mY,
        "mWidth", &Sexy::FRect::mWidth,
        "mHeight", &Sexy::FRect::mHeight,

        "Intersects", &Sexy::FRect::Intersects,
        "Intersection", &Sexy::FRect::Intersection,
        "Union", static_cast<Sexy::FRect (Sexy::FRect::*)(const Sexy::FRect&)>(&Sexy::FRect::Union),
        "Contains", sol::overload(
            static_cast<bool (Sexy::FRect::*)(double, double) const>(&Sexy::FRect::Contains),
            static_cast<bool (Sexy::FRect::*)(const Sexy::TPoint<double>&) const>(&Sexy::FRect::Contains)
        ),
        "Offset", sol::overload(
            static_cast<void (Sexy::FRect::*)(double, double)>(&Sexy::FRect::Offset),
            static_cast<void (Sexy::FRect::*)(const Sexy::TPoint<double>&)>(&Sexy::FRect::Offset)
        ),
        "Inflate", &Sexy::FRect::Inflate,
        sol::meta_function::to_string, [](const Sexy::FRect& r) {
            return "FRect(" + std::to_string(r.mX) + "," + std::to_string(r.mY) + "," +
                   std::to_string(r.mWidth) + "," + std::to_string(r.mHeight) + ")";
        },
        sol::meta_function::equal_to, &Sexy::FRect::operator==
    );
}