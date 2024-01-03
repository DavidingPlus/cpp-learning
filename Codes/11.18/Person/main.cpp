#include <iostream>
using namespace std;
#include <string.h>

//第一种解决方式,直接包含 源文件
// #include "person.cpp"

//第二种解决方式,将.h和.cpp中的内容写到一起,将后缀名改为.hpp文件
#include "person.hpp"

//类模板的分文件编写问题以及解决
// template <typename T1, typename T2>
// class Person
// {
// public:
//     Person(T1 name, T2 age);

//     T1 m_Name;
//     T2 m_Age;

//     void showPerson();
// };

// template <typename T1, typename T2>
// Person<T1, T2>::Person(T1 name, T2 age)
// {
//     this->m_Age = age;
//     this->m_Name = name;
// }

// template <typename T1, typename T2>
// void Person<T1, T2>::showPerson()
// {
//     cout << "姓名: " << this->m_Name << " 年龄: " << this->m_Age << endl;
// }

void test01()
{
    Person<string, int> p("Jerry", 18);
    p.showPerson();
}

int main()
{
    test01();

    return 0;
}
