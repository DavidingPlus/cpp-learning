#include <iostream>
using namespace std;

//空指针调用成员函数

class Person
{
public:
    void showClassName()
    {
        cout << "this is Person class" << endl;
    }

    void showPersonAge()
    {
        //报错原因是因为传入的指针为 Nullptr
        if (this == nullptr)
            return;
        cout << "age= " << this->m_age << endl;
    }

    int m_age;
};

void test01()
{
    Person *p = nullptr;
    p->showClassName();
    p->showPersonAge();
}

int main()
{
    test01();

    return 0;
}
