#include <iostream>
using namespace std;

//打印数据
void showValue(const int &val)
// const为了防止误操作,防止引用操作时修改了形参而导致实参跟着被改变
{
    // val = 1000;
    cout << "val= " << val << endl;
}

int main()
{
    //常量引用
    //使用场景:用来修饰形参,防止误操作

    // int a = 10;

    //加上const之后,编译器将代码修改为 int temp=10;int &ref=temp;
    const int &ref = 10; //引用必须引用一块合法的内存空间
    // ref = 20;            //加入const之后变为只读,不可修改
    cout << "ref= " << ref << endl;

    int a = 100;
    showValue(a);

    cout << "a= " << a << endl;

    return 0;
}