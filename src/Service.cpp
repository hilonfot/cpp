#include "Service.h"
#include "Sunnet.h"
#include <iostream>
#include <unistd.h>

// 构造函数
Service::Service()
{
    // 初始化锁
    pthread_spin_init(&queueLock, PTHREAD_PROCESS_PRIVATE);
    pthread_spin_init(&inGlobalLock, PTHREAD_PROCESS_PRIVATE);
}

// 创建服务器后触发
void Service::OnInit()
{
    cout << "[" << id << "] OnInit" << endl;
}

// 收到消息时触发
void Service::OnMsg(shared_ptr<BaseMsg> msg)
{
    // SERVICE
    if (msg->type == BaseMsg::TYPE::SERVICE)
    {
        auto m = dynamic_pointer_cast<ServiceMsg>(msg);
        OnServiceMsg(m);
    }
    else if (msg->type == BaseMsg::TYPE::SOCKET_ACCEPT)
    {
        auto m = dynamic_pointer_cast<SocketAcceptMsg>(msg);
        OnAcceptMsg(m);
    }
    else if (msg->type == BaseMsg::TYPE::SOCKET_RW)
    {
        auto m = dynamic_pointer_cast<SocketRWMsg>(msg);
        OnRWMsg(m);
    }
}

// 退出服务时触发
void Service::OnExit()
{
    cout << "[" << id << "] OnExit" << endl;
}

// void 插入消息
void Service::PushMsg(shared_ptr<BaseMsg> msg)
{
    pthread_spin_lock(&queueLock);
    {
        msgQueue.push(msg);
    }
    pthread_spin_unlock(&queueLock);
}

// 取出消息
shared_ptr<BaseMsg> Service::PopMsg()
{
    shared_ptr<BaseMsg> msg = NULL;
    // 取出一条消息
    pthread_spin_lock(&queueLock);
    {
        if (!msgQueue.empty())
        {
            msg = msgQueue.front();
            msgQueue.pop();
        }
    }
    pthread_spin_unlock(&queueLock);

    return msg;
}

// 处理一条消息，返回值代表是否处理
bool Service::ProcressMsg()
{
    shared_ptr<BaseMsg> msg = PopMsg();
    if (msg)
    {
        OnMsg(msg);
        return true;
    }
    else
    {
        return false; // 返回值预示着队列是否为空
    }
}

// 处理N条消息， 返回值代表是否处理
void Service::ProcressMsgs(int max)
{
    for (int i = 0; i < max; i++)
    {
        bool succ = ProcressMsg();
        if (!succ)
        {
            break;
        }
    }
}

// 安全设置InGlobal
void Service::SetInGlobal(bool isIn)
{
    pthread_spin_lock(&inGlobalLock);
    {
        inGlobal = isIn;
    }
    pthread_spin_unlock(&inGlobalLock);
}

// 收到其他服务发来的消息
void Service::OnServiceMsg(shared_ptr<ServiceMsg> msg)
{
    cout << "OnserviceMsg" << endl;
}

// 新连接
void Service::OnAcceptMsg(shared_ptr<SocketAcceptMsg> msg)
{
    cout << "OnAcceptMsg " << msg->clientFd << endl;
}

// 套接字可读可写
void Service::OnRWMsg(shared_ptr<SocketRWMsg> msg)
{
    int fd = msg->fd;
    // 可读
    if (msg->isRead)
    {
        const int BUFFSIZE = 512;
        char buff[BUFFSIZE];
        int len = 0;
        do
        {
            len = read(fd, &buff, BUFFSIZE);
            if (len > 0)
            {
                OnSocketData(fd, buff, len);
            }
        } while (len == BUFFSIZE);

        if (len <= 0 && errno != EAGAIN)
        {
            if (Sunnet::inst->GetConn(fd))
            {
                OnSocketClose(fd);
                Sunnet::inst->CloseConn(fd);
            }
        }
    }

    // 可写(注意没有else)
    if (msg->isWrite)
    {
        if (Sunnet::inst->GetConn(fd))
        {
            OnSocketWritable(fd);
        }
    }
}

// 收到客户端数据
void Service::OnSocketData(int fd, const char *buff, int len)
{
    cout << "OnSocketData  " << fd << "  buff: " << buff << endl;
    // echo
    char writeBuff[3] = {'l', 'p', 'y'};
    write(fd, &writeBuff, 3);
}

// 套接字可写
void Service::OnSocketWritable(int fd)
{
    cout << "OnSocketWritable  " << fd << endl;
}

// 关闭连接前
void Service::OnSocketClose(int fd)
{
    cout << "OnSocketClose  " << fd << endl;
}

// 析构函数
Service::~Service()
{
    pthread_spin_destroy(&queueLock);
    pthread_spin_destroy(&inGlobalLock);
}