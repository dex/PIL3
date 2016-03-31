#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int pack(lua_State *L)
{
    int i, n;

    n = lua_gettop(L);
    lua_newtable(L);
    for (i = 1; i <= n; i++) {
        lua_pushinteger(L, i);  // push k
        lua_pushvalue(L, i);    // push v
        lua_settable(L, -3);    // t[k] = v
    }
    return 1;
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
    lua_register(L, "pack", pack);
    if (luaL_dofile(L, argv[1]) != 0) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        exit(EXIT_FAILURE);
    }
    return 0;
}
