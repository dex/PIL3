#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <limits.h>

#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM <= 501
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

#define luaL_newlib(L, f) do { lua_newtable((L)); luaL_register((L), NULL, f); } while(0)
#endif

#define BITS_PER_WORD (CHAR_BIT*sizeof(unsigned int))
#define I_WORD(i) ((unsigned int)(i) / BITS_PER_WORD)
#define I_BIT(i) (1 << ((unsigned int)(i) % BITS_PER_WORD))

#define checkarray(L) \
    (NumArray *)luaL_checkudata(L, 1, "LuaBook.array")

typedef struct NumArray {
    int size;
    unsigned int values[1]; /* variable part */
} NumArray;

static int getsize (lua_State *L) {
    NumArray *a = checkarray(L);
    lua_pushinteger(L, a->size);
    return 1;
}

static unsigned int *getindex (lua_State *L,
                               unsigned int *mask) {
    NumArray *a = checkarray(L);
    int index = luaL_checkint(L, 2) - 1;
    luaL_argcheck(L, 0 <= index && index < a->size, 2,
                  "index out of range");
    /* return element address */
    *mask = I_BIT(index);
    return &a->values[I_WORD(index)];
}

static int setarray (lua_State *L) {
    unsigned int mask;
    unsigned int *entry = getindex(L, &mask);
    if (!lua_isboolean(L, 3))
        luaL_argerror(L, 3, "expect boolean type");
    if (lua_toboolean(L, 3))
        *entry |= mask;
    else
        *entry &= ~mask;
    return 0;
}

static int getarray (lua_State *L) {
    unsigned int mask;
    unsigned int *entry = getindex(L, &mask);
    lua_pushboolean(L, *entry & mask);
    return 1;
}

int array2string (lua_State *L) {
    NumArray *a = checkarray(L);
    lua_pushfstring(L, "array(%d)", a->size);
    return 1;
}

static int newarray (lua_State *L) {
    int i;
    size_t nbytes;
    NumArray *a;
    int n = luaL_checkint(L, 1);
    luaL_argcheck(L, n >= 1, 1, "invalid size");
    nbytes = sizeof(NumArray) + I_WORD(n - 1)*sizeof(unsigned int);
    a = (NumArray *)lua_newuserdata(L, nbytes);
    a->size = n;
    for (i = 0; i <= I_WORD(n - 1); i++)
        a->values[i] = 0; /* initialize array */

    luaL_getmetatable(L, "LuaBook.array");
    lua_setmetatable(L, -2);

    return 1;
}

/* new userdatum is already on the stack */
static const struct luaL_Reg arraylib_f [] = {
    {"new", newarray},
    {NULL, NULL}
};

static const struct luaL_Reg arraylib_m [] = {
    {"__newindex", setarray},
    {"__index", getarray},
    {"__len", getsize},
    {"__tostring", array2string},
    {NULL, NULL}
};

int luaopen_array (lua_State *L) {
    luaL_newmetatable(L, "LuaBook.array");
    luaL_setfuncs(L, arraylib_m, 0);
    luaL_newlib(L, arraylib_f);
    return 1;
}
