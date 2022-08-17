#include <stdio.h>
#include <mysql.h>

// g++ -o main mysql.cpp -I /usr/include/mysql/ -l mysqlclient
int main()
{
    MYSQL *conn_prt;             // 创建一个MYSQL句柄
    conn_prt = mysql_init(NULL); // 初始化MYSQL句柄
    if (!conn_prt)
    {
        printf("connet mysql failed");
        return -1;
    }

    // 尝试与mysql数据库连接
    if (!mysql_real_connect(conn_prt, "127.0.0.1", "root", "522923080", "db_log", 0, NULL, 0))
    {
        printf("fail to connect mysql:%s \n", mysql_error(conn_prt));
    }
    else
    {
        printf("connect success...........\n");
    }

    // 关闭mysql数据库连接，并释放相应内存
    mysql_close(conn_prt);
    return 0;
}