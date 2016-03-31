#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int reverse(lua_State *L)
{
    int i, n;

    n = lua_gettop(L);
    for (i = n; i >= 1; i--) {
        int idx = n-i+1;
        lua_insert(L, idx);
    }
    return n;
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
    lua_register(L, "reverse", reverse);
    if (luaL_dofile(L, argv[1]) != 0) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        exit(EXIT_FAILURE);
    }
    return 0;
}
