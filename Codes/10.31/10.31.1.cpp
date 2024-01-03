#include <iostream>
using namespace std;

//赋值运算符重载

class Person
{
public:
    Person(int age)
    {
        m_Age = new int(age);
    }

    ~Person()
    {
        if (m_Age)
        {
            delete m_Age;
            m_Age = nullptr;
        }
    }

    //重载 赋值运算符
    Person &operator=(Person &p)
    //返回引用!!!!不要返回值,返回值是新建了一个对象!!!!!
    {
        //编译器是提供浅拷贝
        // this->m_Age = p.m_Age;

        //应该先判断是否有属性在堆区,如果有,先释放干净,再深拷贝
        if (m_Age)
        {
            delete m_Age;
            m_Age = nullptr;
        }
        //深拷贝
        this->m_Age = new int(*p.m_Age);
        return *this;
    }

    int *m_Age;
};

void test01()
{
    Person p1(18), p2(20), p3(30);

    p3 = p2 = p1; //赋值操作

    cout << "p1的年龄为: " << *p1.m_Age << endl
         << "p2的年龄为: " << *p2.m_Age << endl
         << "p3的年龄为: " << *p3.m_Age << endl;
}

int main()
{
    test01();

    return 0;
}
