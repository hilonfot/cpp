#include <iostream>
#include "Sunnet.h"
using namespace std;

// 单例
Sunnet *Sunnet::inst;
Sunnet::Sunnet()
{
    inst = this;
}

// 开启系统
void Sunnet::Start()
{
    cout << "hello sunnet! " << endl;
    // 锁
    pthread_rwlock_init(&servicesLock, NULL);
    pthread_spin_init(&globalLock, PTHREAD_PROCESS_PRIVATE);
    // 开启Woker
    StartWorker();
}

// 开启线程
void Sunnet::StartWorker()
{
    for (int i = 0; i < WORKER_NUM; i++)
    {
        cout << "Start worker thread:" << i << endl;
        // 创建线程对象
        Worker *worker = new Worker();
        worker->id = i;
        worker->eachNum = 2 << i;
        // 创建线程
        thread *wt = new thread(*worker);
        // 添加到数组
        workers.push_back(worker);
        workerThreads.push_back(wt);
    }
}

// 等待
void Sunnet::Wait()
{
    if (workerThreads[0])
    {
        workerThreads[0]->join();
    }
}

// 新建服务
uint32_t Sunnet::NewService(shared_ptr<string> type)
{
    auto srv = make_shared<Service>();
    srv->type = type;
    pthread_rwlock_wrlock(&servicesLock);
    {
        srv->id = maxId;
        maxId++;
        services.emplace(srv->id, srv);
    }
    pthread_rwlock_unlock(&servicesLock);
    srv->OnInit();
    return srv->id;
}

// 由id查找服务
shared_ptr<Service> Sunnet::GetService(uint32_t id)
{
    shared_ptr<Service> srv = NULL;
    pthread_rwlock_rdlock(&servicesLock);
    {
        unordered_map<uint32_t, shared_ptr<Service>>::iterator
            iter = services.find(id);
        if (iter != services.end())
        {
            srv = iter->second;
        }
    }
    pthread_rwlock_unlock(&servicesLock);
    return srv;
}

// 删除服务，只能service自己调用自己，因为会调用不加锁的srv->OnExit()和srv->isExiting()
void Sunnet::KillService(uint32_t id)
{
    shared_ptr<Service> srv = GetService(id);
    if (!srv)
    {
        return;
    }
    // 退出前
    srv->OnExit();
    srv->isExiting = true;
    // 删除表
    pthread_rwlock_wrlock(&servicesLock);
    {
        services.erase(id);
    }
    pthread_rwlock_unlock(&servicesLock);
}

// 弹出全局队列
shared_ptr<Service> Sunnet::PopGlobalQueue()
{
    shared_ptr<Service> srv = NULL;
    pthread_spin_lock(&globalLock);
    {
        if (!globalQueue.empty())
        {
            srv = globalQueue.front();
            globalQueue.pop();
            gloabalLen--;
        }
    }
    pthread_spin_unlock(&globalLock);
    return srv;
}

// 插入全局队列
void Sunnet::PushGlobalQueue(shared_ptr<Service> srv)
{
    pthread_spin_lock(&globalLock);
    {
        globalQueue.push(srv);
        gloabalLen++;
    }
    pthread_spin_unlock(&globalLock);
}

// 测试
shared_ptr<BaseMsg> Sunnet::MakeMsg(uint32_t source, char* buff,int len){
    auto msg = make_shared<ServiceMsg>();
    msg->type = BaseMsg::TYPE::SERVICE;
    msg->source = source;
    // 基本类型的对象没有析构函数，
    // 所以用delete 或 delete[] 都可以销毁基本类型数组;
    // 智能指针默认使用delete销毁对象
    // 所以无需重写智能指针的销毁方法
    msg->buff = shared_ptr<char>(buff);
    msg->size = len;
        
    return msg;
}