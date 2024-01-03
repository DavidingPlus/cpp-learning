#include <iostream>
#include <string.h>
using namespace std;

//模板的局限性
//模板并不是万能的,有些特定数据类型,需要用具体化方式做特殊实现

class Person
{
public:
    Person(string name, int age) : m_Name(name), m_Age(age) {}

    // bool operator==(Person &p)
    // {
    //     if (this->m_Age == p.m_Age && this->m_Name == p.m_Name)
    //         return true;
    //     else
    //         return false;
    // }

    //姓名
    string m_Name;
    //年龄
    int m_Age;
};

//对比两个数据是否相等函数
template <typename T>
bool myCompare(T &a, decltype(a) &b)
{
    if (a == b)
        return true;
    else
        return false;
}

//利用具体化Person的版本来实现代码,具体化优先调用
template <>
bool myCompare(Person &p1, decltype(p1) &p2)
{
    if (p1.m_Age == p2.m_Age && p1.m_Name == p2.m_Name)
        return true;
    else
        return false;
}

void test01()
{
    int a = 10, b = 20;
    bool ret = myCompare(a, b);
    if (ret)
        cout << "a == b" << endl;
    else
        cout << "a != b" << endl;
}

void test02()
{
    Person p1("Tom", 10);
    Person p2("Tom", 10);
    //自定义数据类型，不会调用普通的函数模板
    //可以创建具体化的Person数据类型的模板，用于特殊处理这个类型
    bool ret = myCompare(p1, p2);
    if (ret)
    {
        cout << "p1 == p2 " << endl;
    }
    else
    {
        cout << "p1 != p2 " << endl;
    }
}

int main()
{
    // test01();
    test02();

    return 0;
}
