#pragma once
#include <queue>
#include <thread>
#include <Msg.h>

using namespace std;

class Service {
public:
    // 为了效率灵活放public
    
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
private:
    // 取出一条消息
    shared_ptr<BaseMsg> PopMsg();    
};