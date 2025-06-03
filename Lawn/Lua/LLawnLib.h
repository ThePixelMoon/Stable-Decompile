#pragma once

#include <lua.hpp>
#include "LuaManager.h"

void open_todcommon(sol::state_view lua);
void open_toddebug(sol::state_view lua);
void open_rect(sol::state_view lua);
void open_point(sol::state_view lua);
void open_pak(sol::state_view lua);
void open_color(sol::state_view lua);
void open_matrix(sol::state_view lua);
void open_bassmusic(sol::state_view lua);
void open_typecheck(sol::state_view lua);
void open_keycodes(sol::state_view lua);

void lawn_openlibs(sol::state& lua);