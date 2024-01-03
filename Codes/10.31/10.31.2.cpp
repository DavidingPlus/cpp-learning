#include <iostream>
#include <string.h>
using namespace std;

//���ع�ϵ�����

class Person
{
public:
    Person(string name, int age) : m_Name(name), m_Age(age) {}

    //����==��
    bool operator==(Person &p)
    {
        if (this->m_Age == p.m_Age && this->m_Name == p.m_Name)
            return true;
        return false;
    }

    //����!=��
    bool operator!=(Person &p)
    {
        if (this->m_Age == p.m_Age && this->m_Name == p.m_Name)
            return false;
        return true;
    }

    string m_Name;
    int m_Age;
};

void test01()
{
    Person p1("Tom", 18), p2("Tom", 20);

    if (p1 == p2)
        cout << "p1 �� p2 ����ȵ�" << endl;
    else
        cout << "p1 �� p2 �ǲ���ȵ�" << endl;

    if (p1 != p2)
        cout << "p1 �� p2 �ǲ���ȵ�" << endl;
    else
        cout << "p1 �� p2 ����ȵ�" << endl;
}

int main()
{
    test01();

    return 0;
}