#include <iostream>
using namespace std;

//��ģ���Ա��������ʵ��
template <typename T1, typename T2>
class Person
{
public:
    //��Ա������������
    Person(T1 name, T2 age);
    void showPerson();

public:
    T1 m_Name;
    T2 m_Age;
};

//���캯������ʵ��
template <typename T1, typename T2>
Person<T1, T2>::Person(T1 name, T2 age)
{
    this->m_Name = name;
    this->m_Age = age;
}

//��Ա��������ʵ��
template <typename T1, typename T2>
void Person<T1, T2>::showPerson()
{
    cout << "����: " << this->m_Name << " ����: " << this->m_Age << endl;
}

void test01()
{
    Person<string, int> p("Tom", 20);
    p.showPerson();
}

int main()
{
    test01();

    return 0;
}