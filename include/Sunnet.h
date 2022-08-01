#pragma once
#include <vector>
#include "Worker.h"
#include "Service.h"
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

private:
    // 工作线程
    int WORKER_NUM = 3;             // 工作线程数(配置)
    vector<Worker *> workers;       // worker对象
    vector<thread *> workerThreads; // 线程s
private:
    // 开启工作线程
    void StartWorker();
    // 获取服务
    shared_ptr<Service> GetService(uint32_t id);
    // 全局队列
    queue<shared_ptr<Service>> globalQueue;
    int gloabalLen = 0;            // 队列长度
    pthread_spinlock_t globalLock; // 锁
};
