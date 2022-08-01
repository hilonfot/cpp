#pragma once
#include <thread>
#include "Sunnet.h"
#include "Service.h"

class Sunnet;
using namespace std;

class Worker
{
public:
    // 编号
    int id;
    // 每次处理多少条消息
    int eachNum;
    // 线程函数
    void operator()();

private:
    // 辅助函数
    void CheckAndPutGlobal(shared_ptr<Service> srv);
};