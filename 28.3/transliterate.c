#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int transliterate(lua_State *L)
{
    int i;
    size_t len, val_len;
    luaL_Buffer B;
    const char *str, *val;
    char c;

    str = luaL_checklstring(L, 1, &len);
    luaL_checktype(L, 2, LUA_TTABLE);
    luaL_buffinit(L, &B);
    for (i = 0; i<len; i++) {
        lua_pushfstring(L, "%c", str[i]);
        lua_gettable(L, 2);
        switch (lua_type(L, -1)) {
            case LUA_TNIL:
                // copy this char
                lua_pop(L, 1);
                luaL_addchar(&B, str[i]);
                break;
            case LUA_TBOOLEAN:
                if (lua_toboolean(L, -1)) { // true => error ?
                    lua_pushstring(L, "invalid value: true");
                    lua_error(L);
                }
                // false => skip this char
                lua_pop(L, 1);
                break;
            case LUA_TSTRING:
                val = luaL_checklstring(L, -1, &val_len);
                if (val_len != 1) {
                    lua_pushstring(L, "invalid value: not a char");
                    lua_error(L);
                }
                c = val[0];
                lua_pop(L, 1);
                luaL_addchar(&B, c);
                break;
            default:
                lua_pushstring(L, "invalid value");
                lua_error(L);
        }
    }
    luaL_pushresult(&B);
    return 1;
}

int main(int argc, char *argv[])
{
    lua_State *L = NULL;
    
    if (argc < 2)
        return 1;

    L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "transliterate", transliterate);
    if (luaL_dofile(L, argv[1]) != 0) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        return -1;
    }
    return 0;
}


