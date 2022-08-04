#include "SocketWorker.h"
#include <iostream>
#include <unistd.h>

// 初始化
void SocketWorker::Init()
{
    cout << "SocketWorker Init " << endl;
}

void SocketWorker::operator()()
{
    while (true)
    {
        cout << "SocketWorker working " << endl;
        usleep(1000);
    }
}