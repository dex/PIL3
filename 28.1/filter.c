#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int filter(lua_State *L)
{
    int n, i, j, k;

    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TFUNCTION);

    lua_newtable(L);    // result table
    n = lua_objlen(L, 1);

    for (i = 1, j=1; i <= n; i++) {
        lua_pushvalue(L, 2);    // copy function
        lua_rawgeti(L, 1, i);   // push the t[i]
        lua_call(L, 1, 1);      // call f(t[i])
        k = lua_toboolean(L, -1); // get result of f()
        lua_pop(L, 1);          // pop the result
        if (k) {
            lua_rawgeti(L, 1, i);
            lua_rawseti(L, -2, j++);   // set result to table
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    lua_State *L = NULL;
    
    if (argc < 2)
        return 1;

    L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "filter", filter);
    if (luaL_dofile(L, argv[1]) != 0) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        return -1;
    }
    return 0;
}
