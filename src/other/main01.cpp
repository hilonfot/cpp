#include <iostream>
using namespace std;

// 04.数据结构
// typedef struct Books
// {
//    char title[50];
//    char author[50];
//    char subject[100];

//    int book_id;
// }Books;

// void print_book(struct Books *book);

// int main(){
//    Books book1;
//    strcpy(book1.title,"cpp入门到入土");
//    strcpy(book1.author,"c++");
//    strcpy(book1.subject,"计算机");
//    book1.book_id = 10001;

//    print_book(&book1);
// }

// void print_book(Books *book){
//    cout << "book title:"  << book->title << endl;
//    cout << "book author:"  << book->author << endl;
//    cout << "book subject:"  << book->subject << endl;
//    cout << "book id:"  << book->book_id << endl;
// }

// 03.标准输入流
// int main(){
//    char name[50];
//    cout << "请输入您的名称：";
//    cin >> name;
//    cout << "your name:" << name << endl;
//    return 0;
// }

// 02.当前日期和时间
// int main(){
//    // 基于当前系统的当前日期/时间
//    time_t now = time(0);
//    // 把now转换为字符串形式
//    char* dt = ctime(&now);

//    cout << "本地日期和时间：" << dt << endl;

//    // 把now转换为tm结构
//    tm *gmtm = gmtime(&now);

//    dt = asctime(gmtm);
//    cout << "UTC 日期和时间" << dt << endl;

//    return 0;
// }

// 01.引用
// int main(){
//    // 声明简单的变量
//    int i;
//    double d;

//    // 声明阴用变量
//    int& r=i;
//    double& s=d;

//    i=5;
//    cout << "Value of i:" << i << endl;
//    cout << "Value of i reference:" << r <<endl;

//    d = 11.7;
//    cout << "Value of d:" << d << endl;
//    cout << "Value of d referernce:" << s << endl;

//    return 0;
// }