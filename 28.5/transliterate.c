#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define KEY "value"

static void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup) {
    luaL_checkstack(L, nup+1, "too many upvalues");
    for (; l->name != NULL; l++) {  /* fill the table with given functions */
        int i;
        lua_pushstring(L, l->name);
        for (i = 0; i < nup; i++)  /* copy upvalues to the top */
            lua_pushvalue(L, -(nup+1));
        lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
        lua_settable(L, -(nup + 3));
    }
    lua_pop(L, nup);  /* remove upvalues */
}

static int settrans(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_setfield(L, lua_upvalueindex(1), KEY);
    return 0;
}

static int gettrans(lua_State *L)
{
    lua_getfield(L, lua_upvalueindex(1), KEY);
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
    lua_getfield(L, lua_upvalueindex(1), KEY);
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
    luaL_setfuncs(L, methods, 1);
    return 1;
}
