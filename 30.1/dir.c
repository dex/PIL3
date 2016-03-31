#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"

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

/* forward declaration for the iterator function */
static int dir_iter(lua_State *L);

static int l_dir(lua_State *L)
{
	const char *path = luaL_checkstring(L, 1);
	/* create a userdatum to store a DIR address */
	DIR **d = (DIR **)lua_newuserdata(L, sizeof(DIR *));
	/* set its metatable */
	luaL_getmetatable(L, "LuaBook.dir");
	lua_setmetatable(L, -2);
	/* try to open the given directory */
	*d = opendir(path);
	if (*d == NULL)  /* error opening the directory? */
		luaL_error(L, "cannot open %s: %s", path, strerror(errno));
	/* creates and returns the iterator function;
	   its sole upvalue, the directory userdatum,
	   is already on the top of the stack */
	lua_pushcclosure(L, dir_iter, 1);
	return 1;
}

static int dir_iter(lua_State *L)
{
	DIR **d = (DIR **)lua_touserdata(L, lua_upvalueindex(1));
	struct dirent *entry;
	if (*d != NULL && (entry = readdir(*d)) != NULL) {
		lua_pushstring(L, entry->d_name);
		return 1;
    } else {
        if (*d) {
            closedir(*d);
            *d = NULL;
        }
        return 0;  /* no more values to return */
    }
}

static int dir_gc(lua_State *L)
{
	DIR *d = *(DIR **)lua_touserdata(L, 1);
	if (d) closedir(d);
	return 0;
}

static const struct luaL_Reg dirlib [] = {
	{"open", l_dir},
	{NULL, NULL}
};

int luaopen_dir(lua_State *L)
{
	luaL_newmetatable(L, "LuaBook.dir");
	/* set its __gc field */
	lua_pushcfunction(L, dir_gc);
	lua_setfield(L, -2, "__gc");
	/* create the library */
	luaL_newlib(L, dirlib);
	return 1;
}
  

