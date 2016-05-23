#include <stdio.h>
#include <time.h>
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
	lua_pushnumber(L, (double)(tv.tv_usec/1.0e6));
	return 3;
}

/* Returns current EPOCH time in format seconds.microseconds */
int t_now (lua_State *L){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	lua_pushnumber(L, tv.tv_sec + tv.tv_usec/1.0e6);
	return 1;
}

/* 
Sleeps, eg. pauses code execution for given amount of seconds 
Shamelessly ripped from LuaSocket.
*/
int t_sleep(lua_State *L)
{
    double n = luaL_checknumber(L, 1);
    struct timespec t, r;
    if (n < 0.0) n = 0.0;
    if (n > INT_MAX) n = INT_MAX;
    t.tv_sec = (int) n;
    n -= t.tv_sec;
    t.tv_nsec = (int) (n * 1000000000);
    if (t.tv_nsec >= 1000000000) t.tv_nsec = 999999999;
    while (nanosleep(&t, &r) != 0) {
        t.tv_sec = r.tv_sec;
        t.tv_nsec = r.tv_nsec;
    }
    return 0;
}

const struct luaL_reg time_lib[] = {
	//{"getDiff", t_diff},
	{"getTime", t_getTime},
	{"now", t_now},
	{"sleep", t_sleep},
	{NULL, NULL}
};

LUALIB_API int luaopen_libtime (lua_State *L) {
	luaL_register(L, "libtime", time_lib);
	return 1;
}
