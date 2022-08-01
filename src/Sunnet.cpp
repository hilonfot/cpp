#include <iostream>
#include "Sunnet.h"
using namespace std;

// 单例
Sunnet* Sunnet::inst;
Sunnet::Sunnet(){
    inst = this;
}

// 开启系统
void Sunnet::Start(){
    cout << "hello sunnet! " << endl;
    // 锁
    pthread_rwlock_init(&servicesLock,NULL);
    // 开启Woker 
    StartWorker();
}

// 开启线程
void Sunnet::StartWorker(){
    for (int i=0;i<WORKER_NUM;i++){
        cout << "Start worker thread:" << i << endl;
        // 创建线程对象
        Worker* worker = new Worker();
        worker->id = i;
        worker->eachNum = 2<<i;
        // 创建线程
        thread* wt = new thread(*worker);
        // 添加到数组
        workers.push_back(worker);
        workerThreads.push_back(wt);
    }
}

// 等待
void Sunnet::Wait(){
    if (workerThreads[0]){
        workerThreads[0] -> join();
    }
}

// 新建服务
uint32_t Sunnet::NewService(shared_ptr<string> type){
    auto srv = make_shared<Service>();
    srv->type = type;
    pthread_rwlock_wrlock(&servicesLock);
    {
        srv->id = maxId;
        maxId++;
        services.emplace(srv->id,srv);
    }
    pthread_rwlock_unlock(&servicesLock);
    srv->OnInit();
    return srv->id;
}

// 由id查找服务
shared_ptr<Service> Sunnet::GetService(uint32_t id){
    shared_ptr<Service> srv = NULL;
    pthread_rwlock_rdlock(&servicesLock);
    {
        unordered_map<uint32_t,shared_ptr<Service>>::iterator 
        iter = services.find(id);
        if (iter != services.end()){
            srv = iter->second;
        }
    }
    pthread_rwlock_unlock(&servicesLock);
    return srv;
}

// 删除服务，只能service自己调用自己，因为会调用不加锁的srv->OnExit()和srv->isExiting()
void Sunnet::KillService(uint32_t id){
    shared_ptr<Service> srv = GetService(id);
    if (!srv){
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