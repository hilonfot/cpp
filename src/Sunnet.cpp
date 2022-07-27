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