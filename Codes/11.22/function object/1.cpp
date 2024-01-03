#include <iostream>
using namespace std;
#include <cstring>

/*
**概念：**
* 重载函数调用操作符的类，其对象常称为函数对象
* 函数对象使用重载的()时，行为类似函数调用，也叫仿函数

**本质：**
函数对象(仿函数)是一个类，不是一个函数
*/

//函数对象(仿函数)

// 1.函数对象在使用时，可以像普通函数那样调用, 可以有参数，可以有返回值
class myAdd
{
public:
    int operator()(int val1, int val2) const { return val1 + val2; }
};

void test01()
{
    myAdd myadd;
    cout << myadd(10, 10) << endl;
}

// 2.函数对象超出普通函数的概念，函数对象可以有自己的状态
class myPrint
{
public:
    myPrint(int count = 0) {}
    void operator()(string str)
    {
        cout << str << endl;
        ++this->count;
    }

    int count;
};

void test02()
{
    myPrint myprint;
    myprint("hello world");
    myprint("hello world");
    myprint("hello world");
    cout << "myprint调用次数为: " << myprint.count << endl;
}

// 3.函数对象可以作为参数传递
void doPrint(myPrint &mp, string &&str)
{
    mp(str);
}

void test03()
{
    myPrint myprint;
    doPrint(myprint, "hello c++");
}

int main()
{
    // test01();
    // test02();
    test03();

    return 0;
}
