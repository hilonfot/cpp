#include "LuaAPI.h"
#include "stdint.h"
#include "Sunnet.h"
#include <unistd.h>
#include <string.h>

// 开启新服务
int LuaAPI::NewService(lua_State *luaState)
{
    // 参数个数
    int num = lua_gettop(luaState);
    // 参数1: 服务类型
    if (lua_isstring(luaState, 1) == 0)
    {
        // 1 是 2 不是
        lua_pushinteger(luaState, -1);
        return 1;
    }
    size_t len = 0;
    const char *type = lua_tolstring(luaState, 1, &len);
    char *newstr = new char[len + 1];
    newstr[len] = '\0';
    memcpy(newstr, type, len);
    auto t = make_shared<string>(newstr);
    // 处理
    uint32_t id = Sunnet::inst->NewService(t);
    // 返回值
    lua_pushinteger(luaState, id);
    return 1;
}

void LuaAPI::Register(lua_State *luaState)
{
    static luaL_Reg lualibs[] = {
        {"NewService", NewService},
        // {"KillService",KillService},
        // {"Send",Send},

        // {"Listen",Listen},
        // {"CloseConn",CloseConn},
        // {"Write",Write},
        {NULL, NULL}};
    luaL_newlib(luaState, lualibs);
    lua_setglobal(luaState, "sunnet");
}

// int LuaAPI::OnInit(lua_State *luaState)
// {}

// int LuaAPI::NewService(lua_State *luaState)
// {}