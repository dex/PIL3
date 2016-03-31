#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int sum(lua_State *L)
{
    int i, n;
    lua_Number sum = 0;

    n = lua_gettop(L);
    for (i = 1; i <= n; i++)
        sum += luaL_checknumber(L, i);
    lua_pushnumber(L, sum);
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
    lua_register(L, "summation", sum);
    if (luaL_dofile(L, argv[1]) != 0) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        exit(EXIT_FAILURE);
    }
    return 0;
}
