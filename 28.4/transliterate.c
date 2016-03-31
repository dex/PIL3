#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define KEY "value"

static int ref = 0;

static int settrans(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    lua_pushvalue(L, 1);
    lua_setfield(L, -2, KEY);
    return 0;
}

static int gettrans(lua_State *L)
{
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    lua_getfield(L, -1, KEY);
    return 1;
}

static int transliterate(lua_State *L)
{
    int i;
    size_t len, val_len;
    luaL_Buffer B;
    const char *str, *val;
    char c;

    str = luaL_checklstring(L, 1, &len);
    lua_settop(L, 1);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    lua_getfield(L, -1, KEY);
    lua_replace(L, -2);
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

const luaL_Reg methods[] = {
    {"settrans", settrans},
    {"gettrans", gettrans},
    {"transliterate", transliterate},
    {NULL, NULL}

};

int luaopen_transliterate(lua_State *L)
{
    lua_newtable(L);
    lua_newtable(L);
    ref = luaL_ref(L, LUA_REGISTRYINDEX);
    luaL_register(L, NULL, methods);
    return 1;
}
