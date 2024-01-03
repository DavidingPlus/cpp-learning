#include <iostream>
using namespace std;

//函数重载的注意事项
// 1.引用作为重载的条件
void func(int &a) // int &a=10;  不合法
{
    cout << "func(int &a)调用 " << endl;
}

void func(const int &a) // const int &a=10; 合法
{
    cout << "func(const int &a)调用 " << endl;
}

// 2.函数重载碰到默认参数
void func2(int a, int b = 10)
{
    cout << "func2(int a,int b)调用 " << endl;
}

void func2(int a)
{
    cout << "func2(int a)调用 " << endl;
}

int main()
{
    int a = 10;
    func(a);

    func(10);

    // func2(10); //当函数重载碰到默认参数,出现二义性,会报错,尽量避免这种情况

    return 0;
}
