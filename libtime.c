#include <stdio.h>
#include <sys/time.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

/* Returns table:
[0] <int> current EPOCH time
[1] <int> microseconds
[2] <double> microseconds as a fraction of a second
*/
int t_getTime (lua_State *L){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	lua_pushnumber(L, tv.tv_sec);
	lua_pushnumber(L, tv.tv_usec);
	lua_pushnumber(L, (double)(tv.tv_usec * 0.000001));
	return 3;
}

/* Returns current EPOCH time in format seconds.microseconds */
int t_now (lua_State *L){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	lua_pushnumber(L, (double)(tv.tv_sec + (tv.tv_usec * 0.000001)));
	return 1;
}

const struct luaL_reg time_lib[] = {
	//{"getDiff", t_diff},
	{"getTime", t_getTime},
	{"now", t_now},
	{NULL, NULL}
};

LUALIB_API int luaopen_libtime (lua_State *L) {
	luaL_register(L, "libtime", time_lib);
	return 1;
}
