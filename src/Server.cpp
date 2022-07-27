#include "Server.h"
#include "Sunnet.h"
#include <iostream>

// 构造函数
Service::Service(){
    // 初始化锁
    pthread_spin_init(&queueLock, PTHREAD_PROCESS_PRIVATE);
}

// 析构函数
Service::~Service(){
    pthread_spin_destroy(&queueLock);
}