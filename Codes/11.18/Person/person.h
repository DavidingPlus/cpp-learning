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
