#pragma once
using namespace std;

class SocketWorker
{
public:
    void Init();
    // 线程函数
    void operator()();
};