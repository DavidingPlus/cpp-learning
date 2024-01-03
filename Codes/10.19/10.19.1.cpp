#include <iostream>
using namespace std;

// 1.引用必须要初始化(int&b 错误的)
// 2.引用一旦初始化后,就不可以更改了

int main()
{
    int a = 10;
    int b = 20;
    // int &c; //错误，引用必须初始化
    int &c = a; //一旦初始化后，就不可以更改
    c = b;      //这是赋值操作，不是更改引用

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    system("pause");

    return 0;
}