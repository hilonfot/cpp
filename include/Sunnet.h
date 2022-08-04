#pragma once
#include <vector>
#include "Worker.h"
#include "Service.h"
#include "SocketWorker.h"
#include "Conn.h"
#include <unordered_map>

class Worker;

class Sunnet
{
public:
    // 单例
    static Sunnet *inst;
    // 服务列表
    unordered_map<uint32_t, shared_ptr<Service>> services;
    // 最大ID
    uint32_t maxId = 0;
    // 读写锁
    pthread_rwlock_t servicesLock;

public:
    // 构造函数
    Sunnet();
    // 初始化并运行
    void Start();
    // 等待运行
    void Wait();
    // 增删服务
    uint32_t NewService(shared_ptr<string> type);
    void KillService(uint32_t id);
    // 发送消息
    void Send(uint32_t toId, shared_ptr<BaseMsg> msg);
    // 全局队列操作
    shared_ptr<Service> PopGlobalQueue();
    void PushGlobalQueue(shared_ptr<Service> srv);
    // 测试
    shared_ptr<BaseMsg> MakeMsg(uint32_t source, char *buff, int len);

    // 唤醒工作线程
    void CheckAndWeakUp();
    // 让工作线程等待(仅工作线程调用)
    void WorkerWait();

    // 增删查Conn
    int AddConn(int fd, uint32_t id, Conn::TYPE type);
    shared_ptr<Conn> GetConn(int fd);
    bool RemoveConn(int fd);

    // 网络连接操作接口
    int Listen(uint32_t port, uint32_t serviceId);
    void CloseConn(uint32_t fd);

private:
    // 工作线程
    int WORKER_NUM = 3;             // 工作线程数(配置)
    vector<Worker *> workers;       // worker对象
    vector<thread *> workerThreads; // 线程
    // 休眠和唤醒
    pthread_mutex_t sleepMtx;
    pthread_cond_t sleepCond;
    // 休眠工作线程数
    int sleepCount = 0;

    // socket 线程
    SocketWorker *socketWorker;
    thread *socketThread;

    // Conn列表
    unordered_map<uint32_t, shared_ptr<Conn>> conns;
    pthread_rwlock_t connsLock; // 读写锁

private:
    // 开启工作线程
    void StartWorker();
    // 获取服务
    shared_ptr<Service> GetService(uint32_t id);
    // 全局队列
    queue<shared_ptr<Service>> globalQueue;
    int gloabalLen = 0;            // 队列长度
    pthread_spinlock_t globalLock; // 锁

    // 开启Socket线程
    void StartSocket();
};
