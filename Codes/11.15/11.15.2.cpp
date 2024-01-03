#include <iostream>
using namespace std;
#include <string>

//类模板与函数模板的区别

//类模板
template <class NameType, class AgeType = int>
// = int 是指默认参数类型
class Person
{
public:
    Person(NameType name, AgeType age) : m_Name(name), m_Age(age) {}

    void showPerson()
    {
        cout << "name: " << this->m_Name << endl
             << "age: " << this->m_Age << endl;
    }

public:
    NameType m_Name;
    AgeType m_Age;
};

// 1.类模板没有自动类型推导的使用方式
void test01()
{
    // Person p("孙悟空", 1000);//错误,无法用自动类型推导
    Person<string, int> p1("孙悟空", 1000); //正确,只能用显式指定类型
    p1.showPerson();
}

// 2.类模板在模板参数列表中可以有默认参数
//只有类模板可以有默认参数,函数模板不可以!!!
void test02()
{
    Person<string> p2("猪八戒", 999);
    p2.showPerson();
}

int main()
{
    test01();

    return 0;
}
