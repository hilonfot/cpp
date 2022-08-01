#include <fstream>
#include <iostream>
using namespace std;

// 02.异常处理
// double division(int a,int b)
// {
//     if (b == 0 )
//     {
//         throw "err: division by zero condition !";
//     }

//     return (a/b);
// }

// int main()
// {
//     int x= 50;
//     int y=0;
//     double z=0;
//     try{
//         z = division(x,y);
//         cout << z  << endl;
//     }catch(const char* msg){
//         cerr << msg << endl;
//     }

//     return 0;
// }

// 01.读取 & 写入文件
// int main()
// {
//     // -------- 写入 --------
//     char data[100];
//     ofstream outfile;
//     outfile.open("afile.dat");
//     cout << "Writing to the file" << endl;
//     cout << "Enter your name:";
//     cin.getline(data,100);

//     // 向文件写入用户输入的数据
//     outfile << data << endl

//     cout << "Enter your age:";
//     cin >> data;
//     cin.ignore();

//     // 再次向文件写入用户输入的数据
//     outfile << data << endl;

//     // 关闭打开的文件
//     outfile.close();

//     // -------- 读取 --------
//     ifstream infile;
//     infile.open("afile.dat");

//     cout << "Reading from the file" << endl;
//     infile >> data;

//     // 在屏幕上写入数据;
//     cout << data << endl;

//     // 再次从文件读取数据，并显示它
//     infile >> data;
//     cout << data << endl;

//     // 关闭打开的文件
//     infile.close();

//     return 0;
// }