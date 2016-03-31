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

int main(int argc, char *argv[])
{
    lua_State *L = NULL;
    
    if (argc < 2) 
        exit(EXIT_FAILURE);

    if ((L = luaL_newstate()) == NULL) {
        exit(EXIT_FAILURE);
    }
    luaL_openlibs(L);
    lua_register(L, "foreach", foreach);
    if (luaL_dofile(L, argv[1]) != 0) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        exit(EXIT_FAILURE);
    }
    return 0;
}
