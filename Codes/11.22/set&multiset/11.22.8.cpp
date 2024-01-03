#include <iostream>
using namespace std;
#include <set>
#include <cstring>

// set容器排序 存放自定义数据
// 利用仿函数 重载()号运算符 所有需要将排序的规则写成结构体或者类 并且在其中重载()运算符!!!
class Person
{
public:
    Person(string name, int age) : m_Age(age), m_Name(name) {}
    int m_Age;
    string m_Name;
};

struct comparePerson
{
    bool operator()(const Person &p1, const Person &p2) const
    //利用仿函数的时候不要忘了 只读 并且 后面加上const
    {
        //按照年龄进行排序  降序
        return p1.m_Age > p2.m_Age;
    }
};

void test01()
{
    set<Person, comparePerson> s;

    Person p1("刘备", 23);
    Person p2("关羽", 27);
    Person p3("张飞", 25);
    Person p4("赵云", 21);

    s.insert(p1);
    s.insert(p2);
    s.insert(p3);
    s.insert(p4);

    for (set<Person, comparePerson>::iterator iter = s.begin(); iter != s.end(); ++iter)
        cout << "姓名: " << iter->m_Name << " 年龄: " << iter->m_Age << endl;
}

int main()
{
    test01();

    return 0;
}
