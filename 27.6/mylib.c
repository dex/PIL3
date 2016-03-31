#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int foreach(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TFUNCTION);

    lua_pushvalue(L, 2);
    lua_pushnil(L); // first key
    while (lua_next(L, 1) != 0) {
        /* Copy key and keep it */
        lua_pushvalue(L, -2);
        lua_insert(L, -4);
        /* Call function */
        lua_call(L, 2, 0);
        /* Copy function and push to the bottom of key */
        lua_pushvalue(L, 2);
        lua_insert(L, -2);
    }
    return 0;
}
static const struct luaL_Reg mylib[] = {
    { "foreach", foreach },
    { NULL, NULL}
};

int luaopen_mylib(lua_State *L) 
{
    //luaL_newlib(L, mylib);
    lua_newtable(L);
    luaL_register(L, NULL, mylib);
    return 1;
}
