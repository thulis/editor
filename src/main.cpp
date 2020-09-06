extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include "buffer.hpp"

#include <iostream>

#define VERSION "0.7"

int main(void) {
    /* the Lua interpreter */
    lua_State *L;
    /* initialize Lua */
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushstring(L, VERSION);
    lua_setglobal(L, "VERSION");

    /* cleanup Lua */
    lua_close(L);

    GapBuffer buff{20};
    for (int i = 'a'; i < 'z'; i++) buff.insert((char)i);
    buff.move(1);
    for (int i = 'a'; i < 'z'; i++) buff.insert((char)i);
    for (int i = 'a'; i < 'z'; i++) buff.insert((char)i);
    buff.move(2);
    for (int i = 'a'; i < 'z'; i++) buff.insert((char)i);
    buff.insert('\0');
    buff.print();
    
    return 0;
}
