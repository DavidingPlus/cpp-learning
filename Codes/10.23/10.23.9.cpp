#include <iostream>
using namespace std;

//圆周率
const double PI = 3.14;

// C++面向对象的三大特性:封装,继承,多态

//设计一个圆类,求圆的周长
//圆求周长的公式: 2*PI*半径

// class 代表设计一个类,类后面紧跟着的就是类名称
class Circle
{
    //访问权限
    //公共权限
public:
    //属性
    //半径
    int m_r;

    //行为
    //获取圆的周长
    double calculateZC()
    {
        return 2 * PI * m_r;
    }
};

int main()
{
    //通过圆类来创建一个具体的圆(对象)
    //实例化 (通过一个类 创建一个对象的过程)
    Circle c1{10};
    //给圆对象的属性进行赋值

    // 2 * PI * 10 = 62.8
    cout << "圆的周长为: " << c1.calculateZC() << endl;

    return 0;
}
