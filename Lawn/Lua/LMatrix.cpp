#include "LLawnLib.h"
#include "../../SexyAppFramework/SexyMatrix.h"

using namespace Sexy;

void open_matrix(sol::state_view lua) {
    sol::table sexy;
    if (lua["Sexy"].valid() && lua["Sexy"].get_type() == sol::type::table) {
        sexy = lua["Sexy"];
    } else {
        sexy = lua.create_table();
        lua["Sexy"] = sexy;
    }

    sexy.new_usertype<Sexy::SexyMatrix3>("Matrix3",
        sol::constructors<Sexy::SexyMatrix3()>(),
        "ZeroMatrix", &Sexy::SexyMatrix3::ZeroMatrix,
        "LoadIdentity", &Sexy::SexyMatrix3::LoadIdentity,
        sol::meta_function::multiplication, sol::resolve<Sexy::SexyMatrix3(const Sexy::SexyMatrix3&) const>(&Sexy::SexyMatrix3::operator*),
        sol::meta_function::to_string, [](const Sexy::SexyMatrix3& m) {
            return "Matrix3(...)";
        }
    );

    sexy.new_usertype<Sexy::SexyTransform2D>("Transform2D",
        sol::constructors<
            Sexy::SexyTransform2D(),
            Sexy::SexyTransform2D(bool),
            Sexy::SexyTransform2D(const Sexy::SexyMatrix3&)
        >(),
        sol::base_classes, sol::bases<Sexy::SexyMatrix3>(),

        "Translate", &Sexy::SexyTransform2D::Translate,
        "RotateRad", &Sexy::SexyTransform2D::RotateRad,
        "RotateDeg", &Sexy::SexyTransform2D::RotateDeg,
        "Scale", &Sexy::SexyTransform2D::Scale
    );

    sexy.new_usertype<Sexy::Transform>("Transform",
        sol::constructors<Sexy::Transform()>(),
        "Reset", &Sexy::Transform::Reset,
        "Translate", &Sexy::Transform::Translate,
        "RotateRad", &Sexy::Transform::RotateRad,
        "RotateDeg", &Sexy::Transform::RotateDeg,
        "Scale", &Sexy::Transform::Scale,
        "GetMatrix", &Sexy::Transform::GetMatrix,

        "mTransX1", &Sexy::Transform::mTransX1,
        "mTransY1", &Sexy::Transform::mTransY1,
        "mTransX2", &Sexy::Transform::mTransX2,
        "mTransY2", &Sexy::Transform::mTransY2,
        "mScaleX", &Sexy::Transform::mScaleX,
        "mScaleY", &Sexy::Transform::mScaleY,
        "mRot", &Sexy::Transform::mRot,
        "mHaveRot", &Sexy::Transform::mHaveRot,
        "mHaveScale", &Sexy::Transform::mHaveScale,
        "mComplex", &Sexy::Transform::mComplex
    );
}