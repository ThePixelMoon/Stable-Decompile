#include "LLawnLib.h"

void lawn_openlibs(sol::state& lua) {
	Hook::Init(lua);

	open_todcommon(lua);
    open_toddebug(lua);
	open_rect(lua);
	open_point(lua);
	open_pak(lua);
	open_color(lua);
	open_matrix(lua);
	open_bassmusic(lua);
	open_typecheck(lua);
	open_keycodes(lua);
}