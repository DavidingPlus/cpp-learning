#include <iostream>
using namespace std;

//函数的默认参数

//如果我们自己传入数据,就用自己的数据,如果没有,就用默认值
//语法: 返回值类型 函数名(形参 = 默认值) {}
int func(int a, int b = 20, int c = 30)
{
    return a + b + c;
}

//注意事项
// 1.如果某个位置已经有了默认参数,那么从这个位置往后,从左到右都必须有默认值
// int func2(int a = 10, int b, int c, int d = 10)
// {
//     return a + b + c + d;
// }

// 2.如果函数的声明有了默认参数,函数的实现就不能有默认参数
//声明和实现只能有一个有默认参数(是指只能有一个可以有默认参数,例如下面的第一个a和第二个b是不可以的!!!)
// int func2(int a=10, int b);
// int func2(int a, int b = 10);   error!!!

int func2(int a, int b);

int func2(int a = 10, int b = 10)
{
    return a + b;
}

int main()
{
    // cout << func(10, 30) <<s endl;
    cout << func2() << endl;

    return 0;
}
