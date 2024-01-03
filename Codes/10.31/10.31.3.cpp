#include <iostream>
#include <string.h>
using namespace std;

//函数调用运算符重载

//打印输出类
class MyPrint
{
public:
    //重载函数调用运算符()
    void operator()(string text)
    {
        cout << text << endl;
    }
};

void MyPrint02(string text)
{
    cout << text << endl;
}

void test01()
{
    MyPrint myPrint;

    myPrint("helloworld! "); //由于使用起来非常类似于函数调用,因此称为仿函数!!!
    MyPrint02("helloworld! ");
}

//仿函数非常灵活.没有一个固定写法
//加法类
class MyAdd
{
public:
    int operator()(int num1, int num2)
    {
        return num1 + num2;
    }
};

void test02()
{
    MyAdd myadd;
    int ret = myadd(100, 100);
    cout << ret << endl;

    //匿名函数对象
    cout << MyAdd()(100, 100) << endl;
}

int main()
{
    test01();
    test02();

    return 0;
}
