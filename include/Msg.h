#pragma once
#include <memory>
using namespace std;

// 消息基类
class BaseMsg
{
public:
    // 消息类型
    enum TYPE
    {
        SERVICE = 1,       // 服务间消息
        SOCKET_ACCEPT = 2, // 有新的客户端连接
        SOCKET_RW = 3,     // 客户端可读可写
    };

    uint8_t type;         // 消息类型
    char load[999999]{};  // 用于检测内存泄露，仅用于调试
    virtual ~BaseMsg(){}; // 虚析构
};

// 服务间消息
class ServiceMsg : public BaseMsg
{
public:
    uint32_t source;       // 消息发送方
    shared_ptr<char> buff; // 消息内容
    size_t size;           // 消息内容大小
};

class SocketAcceptMsg : public BaseMsg
{
public:
    int listenFd;
    int clientFd;
};

class SocketRWMsg : public BaseMsg
{
public:
    int fd;
    bool isRead = false;
    bool isWrite = false;
};