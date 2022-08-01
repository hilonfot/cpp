#include "Sunnet.h"

void test()
{
    auto pingType = make_shared<string>("ping");
    uint32_t ping1 = Sunnet::inst->NewService(pingType);
    uint32_t ping2 = Sunnet::inst->NewService(pingType);
    uint32_t pong = Sunnet::inst->NewService(pingType);

    auto msg1 = Sunnet::inst->MakeMsg(ping1, new char[3]{'h', 'i', '\0'}, 3);
    auto msg2 = Sunnet::inst->MakeMsg(ping1, new char[6]{'h', 'e', 'l', 'l', 'o', '\0'}, 6);

    Sunnet::inst->Send(pong, msg1);
    Sunnet::inst->Send(pong, msg2);
}

int main()
{
    new Sunnet();
    Sunnet::inst->Start();
    test();
    // 开启系统后的一些逻辑
    Sunnet::inst->Wait();

    return 0;
}