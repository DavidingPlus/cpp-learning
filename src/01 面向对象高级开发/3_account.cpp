#include <iostream>
using namespace std;

class Account
{
public:
    static double _rate;                      // 静态成员变量一个程序只有一份，类内声明，类外初始化
    static void set_rate(const double &rate); // 静态成员函数，调用时可以声明类对象，可以调用作用域直接访问，类外实现，类外实现的时候不用加关键字static,但是要加作用域
};
// 初始化
double Account::_rate = 8.0;

void Account::set_rate(const double &rate)
{
    Account::_rate = rate;
}

int main()
{
    cout << Account::_rate << endl;
    Account::set_rate(7.0);
    cout << Account::_rate << endl;

    return 0;
}