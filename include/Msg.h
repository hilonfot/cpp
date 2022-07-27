#pragma once 
#include <memory>
#include <stdint.h>
using namespace std;

// 消息基类
class BaseMsg{
public:
    enum TYPE{ // 消息类型 
        SERVICE = 1, 
    };

    uint8_t type; // 消息类型
    char load[999999]{}; // 用于检测内存泄露，仅用于调试
    virtual ~BaseMsg(){};  // 虚析构
};

// 服务间消息
class ServiceMsg: public BaseMsg{
public:
    uint32_t source; // 消息发送方
    shared_ptr<char> buff;// 消息内容
    size_t size; // 消息内容大小  
};