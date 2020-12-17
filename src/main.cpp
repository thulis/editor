extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include "Buffer.h"
#include "Mode.h"

#include <iostream>

#define VERSION "0.7"

extern "C" int average(lua_State* lstate)
{
    /* get number of arguments */
    int n = lua_gettop(lstate);
    double sum = 0;
    int i;

    /* loop through each argument */
    for (i = 1; i <= n; i++)
    {
        if (!lua_isnumber(lstate, i))
        {
            lua_pushstring(lstate, "Incorrect argument to 'average'");
            lua_error(lstate);
        }

        /* total the arguments */
        sum += lua_tonumber(lstate, i);
    }

    /* push the average */
    lua_pushnumber(lstate, sum / n);

    /* push the sum */
    lua_pushnumber(lstate, sum);

    /* return the number of results */
    return 2;
}

int main(void) {
    /* the Lua interpreter */
    lua_State *L;
    /* initialize Lua */
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushstring(L, VERSION);
    lua_setglobal(L, "VERSION");

    lua_register(L, "average", average);
    luaL_dofile(L, "test.lua");

    /* cleanup Lua */
    lua_close(L);

    mode::Normal normalmode{};
    buffer::BufferSettings<mode::Normal> bsettings{20, normalmode};
    buffer::Buffer<mode::Normal> buff{bsettings};

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
