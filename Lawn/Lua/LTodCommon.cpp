#include "LLawnLib.h"
#include "../../Sexy.TodLib/TodCommon.h"

void open_todcommon(sol::state_view lua) {
    sol::table tod;
    if (lua["tod"].valid() && lua["tod"].get_type() == sol::type::table) {
        tod = lua["tod"];
    } else {
        tod = lua.create_table();
        lua["tod"] = tod;
    }

    tod.set("PickFromArray", [](sol::table tbl, int count) {
        std::vector<int> vec;
        vec.reserve(count);
        for (int i = 1; i <= count; ++i)
            vec.push_back(tbl.get<int>(i));
        return TodPickFromArray(vec.data(), count);
    });

    tod.set("PickFromWeightedArray", [](sol::table tbl) {
        std::size_t count = tbl.size();
        if (count == 0)
            throw sol::error("PickFromWeightedArray: expected a non-empty array of tables");
        std::vector<TodWeightedArray> arr(count);
        for (std::size_t i = 1; i <= count; ++i) {
            sol::table entry = tbl.get<sol::table>(i);
            arr[i - 1].mItem = entry.get_or("mItem", 0);
            arr[i - 1].mWeight = entry.get_or("mWeight", 0);
        }
        return TodPickFromWeightedArray(arr.data(), static_cast<int>(count));
    });

    tod.set("LoadResources", [](const std::string& group) { return TodLoadResources(group.c_str()); });
    tod.set("LoadNextResource", []() { return TodLoadNextResource(); });

    tod.set("CurveQuad", [](double t) { return TodCurveQuad((float)t); });
    tod.set("CurveInvQuad", [](double t) { return TodCurveInvQuad((float)t); });
    tod.set("CurveS", [](double t) { return TodCurveS((float)t); });
    tod.set("CurveInvQuadS", [](double t) { return TodCurveInvQuadS((float)t); });
    tod.set("CurveBounce", [](double t) { return TodCurveBounce((float)t); });
    tod.set("CurveQuadS", [](double t) { return TodCurveQuadS((float)t); });
    tod.set("CurveCubic", [](double t) { return TodCurveCubic((float)t); });
    tod.set("CurveInvCubic", [](double t) { return TodCurveInvCubic((float)t); });
    tod.set("CurveCubicS", [](double t) { return TodCurveCubicS((float)t); });
    tod.set("CurvePoly", [](double t, double p) { return TodCurvePoly((float)t, (float)p); });
    tod.set("CurveInvPoly", [](double t, double p) { return TodCurveInvPoly((float)t, (float)p); });
    tod.set("CurvePolyS", [](double t, double p) { return TodCurvePolyS((float)t, (float)p); });
    tod.set("CurveCircle", [](double t) { return TodCurveCircle((float)t); });
    tod.set("CurveInvCircle", [](double t) { return TodCurveInvCircle((float)t); });

    tod.set("CurveEval", [](double t, double s, double e, int curve) {
        return TodCurveEvaluate((float)t, (float)s, (float)e, (TodCurves)curve);
    });
    tod.set("CurveEvalClamped", [](double t, double s, double e, int curve) {
        return TodCurveEvaluateClamped((float)t, (float)s, (float)e, (TodCurves)curve);
    });

    tod.set("AnimateCurveFloat", [](int start, int end, int age, double s, double e, int curve) {
        return TodAnimateCurveFloat(start, end, age, (float)s, (float)e, (TodCurves)curve);
    });
    tod.set("AnimateCurveFloatTime", [](double start, double end, double age, double s, double e, int curve) {
        return TodAnimateCurveFloatTime((float)start, (float)end, (float)age, (float)s, (float)e, (TodCurves)curve);
    });
    tod.set("AnimateCurveInt", [](int start, int end, int age, int s, int e, int curve) {
        return TodAnimateCurve(start, end, age, s, e, (TodCurves)curve);
    });

    tod.set("RandRangeInt", [](int min, int max) { return RandRangeInt(min, max); });
    tod.set("RandRangeFloat", [](double min, double max) { return RandRangeFloat((float)min, (float)max); });

    tod.set("ClampInt", [](int v, int min, int max) { return ClampInt(v, min, max); });
    tod.set("ClampFloat", [](double v, double min, double max) { return ClampFloat((float)v, (float)min, (float)max); });
}