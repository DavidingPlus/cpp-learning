#include <iostream>
using namespace std;
#include <string.h>

//类模板的对象做函数参数
template <typename T1, typename T2>
class Person
{
public:
    Person(T1 name, T2 age) : m_Name(name), m_Age(age) {}

    T1 m_Name;
    T2 m_Age;

    void showPerson()
    {
        cout << "姓名: " << this->m_Name << endl
             << "年龄: " << this->m_Age << endl;
    }
};

// 1.指定传入的类型
void printPerson1(Person<string, int> &p)
{
    p.showPerson();
}

void test01()
{
    Person<string, int> p("孙悟空", 100);
    printPerson1(p);
}

// 2.参数模板化
template <typename T1, typename T2>
void printPerson2(Person<T1, T2> &p)
{
    p.showPerson();
    cout << "T1的类型为: " << typeid(T1).name() << endl;
    cout << "T2的类型为: " << typeid(T2).name() << endl;
}

void test02()
{
    Person<string, int> p("猪八戒", 90);
    printPerson2(p);
}

// 3.整个类模板化
template <typename T>
void printPerson3(T &p)
{
    p.showPerson();
    cout << "T的类型为: " << typeid(T).name() << endl;
}

void test03()
{
    Person<string, int> p("唐僧", 30);
    printPerson3(p);
}

int main()
{
    // test01();
    // test02();
    test03();

    return 0;
}
