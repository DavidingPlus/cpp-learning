#include <iostream>
using namespace std;
#include <list>
#include <cstring>

/*
案例描述 : 将Person自定义数据类型进行排序, Person中属性有姓名、年龄、身高
排序规则：按照年龄进行升序，如果年龄相同按照身高进行降序
*/

// Person类
class Person
{
public:
    Person(string name, int age, int height) : m_Name(name), m_Age(age), m_Height(height) {}
    string &get_Name() { return this->m_Name; }
    int &get_Age() { return this->m_Age; }
    int &get_Height() { return this->m_Height; }

private:
    string m_Name;
    int m_Age;
    int m_Height;
};

//比较函数
bool myCompare(Person &p1, Person &p2)
{
    if (p1.get_Age() != p2.get_Age())
        return p1.get_Age() < p2.get_Age();
    else
        return p1.get_Height() > p2.get_Height();
}

int main()
{
    //数据准备
    list<Person> L;

    Person p1("刘备", 35, 175);
    Person p2("曹操", 45, 180);
    Person p3("孙权", 40, 170);
    Person p4("赵云", 25, 190);
    Person p5("张飞", 35, 160);
    Person p6("关羽", 35, 200);

    L.push_back(p1);
    L.push_back(p2);
    L.push_back(p3);
    L.push_back(p4);
    L.push_back(p5);
    L.push_back(p6);

    //未排序前
    for (list<Person>::iterator iter = L.begin(); iter != L.end(); ++iter)
        cout << "姓名:" << iter->get_Name() << " 年龄: " << iter->get_Age()
             << " 身高: " << iter->get_Height() << endl;

    cout << "---------------------------------" << endl;

    //排序后
    L.sort(myCompare);
    for (auto iter = L.begin(); iter != L.end(); ++iter)
        cout << "姓名:" << iter->get_Name() << " 年龄: " << iter->get_Age()
             << " 身高: " << iter->get_Height() << endl;

    return 0;
}
