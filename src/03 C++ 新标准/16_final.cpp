#include <iostream>
using namespace std;

struct Base1 final // final表示不允许有类继承自己
{
};

//  error
// struct Derived1 : Base1
// {
// };

struct Base2
{
    virtual void f() final; // final表示不允许子类覆写这个函数
};

struct Derived2 : Base2
{
    // void f();//error
};

int main()
{

    return 0;
}