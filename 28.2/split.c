#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int split(lua_State *L)
{
    size_t len;
    const char *s = luaL_checklstring(L, 1, &len); /* subject */
    const char *sep = luaL_checkstring(L, 2); /* separator */
    const char *e;
    int i = 1;
    lua_newtable(L); /* result table */
    /* repeat for each separator */
    while ((e = memchr(s, *sep, len)) != NULL) {
        lua_pushlstring(L, s, e-s); /* push substring */
        lua_rawseti(L, -2, i++); /* insert it in table */
        len -= (e-s+1);
        s = e + 1; /* skip separator */

    }
    /* insert last substring */
    lua_pushlstring(L, s, len);
    lua_rawseti(L, -2, i);
    return 1;
}

int main(int argc, char *argv[])
{
    lua_State *L = NULL;
    
    if (argc < 2)
        return 1;

    L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "split", split);
    if (luaL_dofile(L, argv[1]) != 0) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        return -1;
    }
    return 0;
}

