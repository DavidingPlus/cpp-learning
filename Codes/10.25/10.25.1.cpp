#include <iostream>
using namespace std;

//构造函数的调用规则
// 1.创建一个类,c++编译器会给每个类都添加三个函数
//默认构造 (空实现)
//析构函数 (空实现)
//拷贝构造 (值拷贝)

// 2.
// 如果我们写了有参构造函数,编译器不再提供默认构造,依然提供拷贝构造
// 如果我们写了拷贝构造函数,编译器就不再提供其他构造函数
// 拷贝构造 > 有参构造 > 无参构造 !!!
class Person
{
public:
    // Person()
    // {
    //     cout << "Person的默认构造函数的调用" << endl;
    // }

    Person(int age)
    {
        m_age = age;
        cout << "Person的默认构造函数的调用" << endl;
    }

    // Person(const Person &p)
    // {
    //     m_age = p.m_age;
    //     cout << "Person的拷贝构造函数的调用" << endl;
    // }

    ~Person()
    {
        cout << "Person的析构函数的调用" << endl;
    }

    int m_age;
};

void test01()
{
    Person p1 = 18;

    Person p2(p1);

    cout << "p2的年龄为: " << p2.m_age << endl;
}

void test02()
{
    Person p1(20);

    Person p2(p1);
    cout << "p2的年龄为: " << p2.m_age << endl;
}

int main()
{
    // test01();
    test02();

    return 0;
}
