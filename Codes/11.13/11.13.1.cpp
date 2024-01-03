#include <iostream>
using namespace std;

//函数模板

//交换两个整形交换函数
void swapInt(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//交换两个浮点型函数
void swapDouble(double &a, double &b)
{
    double temp = a;
    a = b;
    b = temp;
}

template <typename T>
void myswap(T &a, decltype(a) &b)
{
    T temp = a;
    a = b;
    b = temp;
}

void test01()
{
    int a = 10, b = 20;
    myswap<int>(a, b);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    double c = 10.1515, d = 20.3698;
    myswap(c, d);
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
}

int main()
{
    test01();

    return 0;
}
