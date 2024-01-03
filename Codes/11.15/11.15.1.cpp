#include <iostream>
using namespace std;
#include <string.h>

//ÀàÄ£°å
template <typename NameType, typename AgeType>
class Person
{
public:
    Person(NameType name, AgeType age) : m_Name(name), m_Age(age) {}

    NameType m_Name;
    AgeType m_Age;

    void showPerson()
    {
        cout << "name: " << this->m_Name << endl
             << "age: " << this->m_Age << endl;
    }
};

void test01()
{
    Person<string, int> p1("ËïÎò¿Õ", 999);
    p1.showPerson();
}

int main()
{
    test01();

    return 0;
}
