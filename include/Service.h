#pragma once
#include <queue>
#include <thread>
#include <Msg.h>
#include "ConnWriter.h"
#include <unordered_map>
using namespace std;

class Service
{
public:
    // 为s了效率灵活放public

    // 唯一id
    uint32_t id;
    // 类型
    shared_ptr<string> type;
    // 是否正在退出
    bool isExiting = false;
    // 消息列表和锁
    queue<shared_ptr<BaseMsg>> msgQueue;
    /*
        MacOx not pthread_spinlock_t
        If the performance of your lock is not critical,
        pthread_mutex_t can be used as a drop replacement for pthread_spinlock_t,
        which makes porting easy.
    */
    pthread_spinlock_t queueLock;
    // 标记是否在全局队列， true: 表示在队列里，或正在处理
    bool inGlobal = false;
    pthread_spinlock_t inGlobalLock;
    // 业务逻辑（仅用于测试）
    unordered_map<int, shared_ptr<ConnWriter>> writers;

public:
    // 构造函数和析构函数
    Service();
    ~Service();
    // 回调函数(编写服务器逻辑)
    void OnInit();
    void OnMsg(shared_ptr<BaseMsg> msg);
    void OnExit();
    // 插入消息
    void PushMsg(shared_ptr<BaseMsg> msg);
    // 执行消息
    bool ProcressMsg();
    void ProcressMsgs(int max);
    // 线程安全地设置inGlobal
    void SetInGlobal(bool isIn);

private:
    // 取出一条消息
    shared_ptr<BaseMsg> PopMsg();
    // 消息处理方法
    void OnServiceMsg(shared_ptr<ServiceMsg> msg);
    void OnAcceptMsg(shared_ptr<SocketAcceptMsg> msg);
    void OnRWMsg(shared_ptr<SocketRWMsg> msg);
    void OnSocketData(int fd, const char *buff, int len);
    void OnSocketWritable(int fd);
    void OnSocketClose(int fd);
};