#pragma once
#include <thread>

class Sunnet;
using namespace std;

class Worker{
    public:
        // 编号
        int id;
        // 每次处理多少条消息
        int eachNum;
        // 线程函数
        void operator()();
};