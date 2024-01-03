#include <iostream>
using namespace std;
#include <vector>
#include <string.h>
#include <algorithm>

// vector容器中存放自定义数据类型
class Person
{
public:
    Person(string name, int age) : m_Name(name), m_Age(age) {}

    string m_Name;
    int m_Age;
};

void myPrint(Person &p)
{
    cout << "姓名: " << p.m_Name << " 年龄: " << p.m_Age << endl;
}

void test01()
{
    vector<Person> v;

    Person p1("aaa", 10);
    Person p2("bbb", 20);
    Person p3("ccc", 30);
    Person p4("ddd", 40);
    Person p5("eee", 50);

    //向容器中添加数据
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);

    //遍历容器中的数据
    // for (vector<Person>::iterator iter = v.begin(); iter < v.end(); ++iter)
    // {
    //     cout << "姓名: " << iter->m_Name << " 年龄: " << iter->m_Age << endl;
    // }

    for_each(v.begin(), v.end(), myPrint);
}

//存放自定义数据类型 指针
void myPrint2(Person *p)
{
    cout << "姓名: " << p->m_Name << " 年龄: " << p->m_Age << endl;
}

void test02()
{
    vector<Person *> v;

    Person p1("aaa", 10);
    Person p2("bbb", 20);
    Person p3("ccc", 30);
    Person p4("ddd", 40);
    Person p5("eee", 50);

    //向容器中添加数据
    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);
    v.push_back(&p5);

    //遍历容器中的数据
    for (vector<Person *>::iterator iter = v.begin(); iter < v.end(); ++iter)
    {
        cout << "姓名: " << (*iter)->m_Name << " 年龄: " << (*iter)->m_Age << endl;
    }

    // for_each(v.begin(), v.end(), myPrint2);
}

int main()
{
    // test01();
    test02();

    return 0;
}
