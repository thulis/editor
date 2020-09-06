extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include <iostream>

#define VERSION "0.7"

//int main(void) {
int lua_main(void) {
    /* the Lua interpreter */
    lua_State *L;
    /* initialize Lua */
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushstring(L, VERSION);
    lua_setglobal(L, "VERSION");

    /* cleanup Lua */
    lua_close(L);

    //GapBuffer buff{20};
    //buff.insert('a');
    //buff.insert('b');
    //buff.insert('c');
    //buff.insert('\0');
    //printf("%s\n", buff.get_ptr());
    //buff.left(2);
    //buff.del();
    //printf("%s\n", buff.get_ptr());
    
    return 0;
}
