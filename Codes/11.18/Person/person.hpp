#pragma once
#include <iostream>
using namespace std;

template <typename T1, typename T2>
class Person
{
public:
    Person(T1 name, T2 age);

    T1 m_Name;
    T2 m_Age;

    void showPerson();
};

template <typename T1, typename T2>
Person<T1, T2>::Person(T1 name, T2 age)
{
    this->m_Age = age;
    this->m_Name = name;
}

template <typename T1, typename T2>
void Person<T1, T2>::showPerson()
{
    cout << "ÐÕÃû: " << this->m_Name << " ÄêÁä: " << this->m_Age << endl;
}
