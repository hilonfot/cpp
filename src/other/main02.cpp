#include <iostream>
using namespace std;

// 05. 抽象类
class Shape
{
    public:
        virtual int  getArea() = 0;
        void setWidth(int w )
        {
            width = w;
        } 
        void setHeight(int h)
        {
            height = h;
        }

    protected:
        int width;
        int height;    
};

// 派生类
class Rectangle: public Shape{
    public:
        int getArea()
        {
            return (width*height);
        }
};

class Triangele: public Shape
{
    public:
        int getArea()
        {
            return (width*height)/2;
        }
};


int main(void)
{
    Rectangle Rect;
    Triangele Tri;

    Rect.setWidth(5);
    Rect.setHeight(7);
    cout << "Total Rectangle area: " << Rect.getArea() << endl;

    Tri.setWidth(5);
    Tri.setHeight(7);
    cout << "Total Triangle area: " << Tri.getArea() << endl;

    return 0;
}

// 04. 多态
// class Shape
// {
//     protected:
//         int width,height;
//     public:
//         Shape(int a =0,int b=0)
//         {
//             width = a;
//             height = b;
//         }    
//         // 纯虚函数
//         virtual void area() = 0;
// };

// class Rectangle: public Shape
// {
//    public:
//     Rectangle(int a=0,int b=0):Shape(a,b){ }
//     void area()
//     {
//         cout << "Rectangle class area: " << (width*height) << endl;
//     }
// };

// class Triangle: public Shape{
//     public:
//         Triangle(int a=0,int b =0):Shape(a,b) {}
//         void area()
//         {
//             cout << "Triangle class area: " << (width *height / 2) << endl;
//         }
// };

// int main()
// {
//     Shape *shape;
//     Rectangle rec(10,7);
//     Triangle tri(10,5);

//     // 存储矩形的地址
//     shape = &rec;
//     // 调用矩形的求面积函数 area
//     shape->area();

//     // 存储三角形的地址
//     shape = &tri;
//     // 调用三角形的求面积函数area
//     shape->area();

//     return 0;
// }

// 03.重载函数
// class printData
// {
//     public:
//         void print(int i)
//         {
//             cout << "整数：" << i << endl;
//         }

//         void print(double f)
//         {
//             cout << "浮点数：" << f << endl;
//         }

//         void print(char c[])
//         {
//             cout << "字符串：" << c << endl;
//         }
// };
// 
// int main(void)
// {
//     printData pd;
//     pd.print(5);
//     pd.print(5.999);
//     char c[] = "五";
//     pd.print(c);

//     return 0;
// }

// 02. 继承
// class Shape 
// {
//     public:
//         void setWidth(int w)
//         {
//             width = w;
//         } 

//         void setHeight(int h)
//         {
//             heightl = h;
//         }

//         protected:
//             int width;
//             int heightl;
// };

// class Rectangle: public Shape
// {
//     public:
//     int getArea()
//     {
//         return (width*heightl);
//     }
// };

// int main(void)
// {
//     Rectangle Rect;
//     Rect.setWidth(5);
//     Rect.setHeight(7);

//     // 输出对象的面积
//     cout << "Total area:" << Rect.getArea() << endl;
//     return 0;
// }

//  01. 类
// class Box
// {
//     public:
//         double length; 
//         double width;
//         double height;
//         // 成员函数声明
//         double get(void);
//         void set(double len,double width,double height);
// };

// // 成员函数定义
// double Box::get(void)
// {
//     return length*width*height;
// }

// void Box::set(double len,double wid,double hei)
// {
//     length = len;
//     width = wid;
//     height = hei;
// }

// int main()
// {
//     Box box;
//     double volume = 0.0; // 体积

//     box.set(12.1,21,9.2);
//     volume = box.get();
//     cout << "体积：" << volume << endl;
//     return 0;
// }