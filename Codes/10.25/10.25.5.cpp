#include <iostream>
using namespace std;

//静态成员
class Person
{
public:
    // 1.所有对象都共享一份数据
    // 2.在编译阶段就分配内存
    // 3.类内声明,类外初始化操作
    static int m_A;

    //静态成员变量也是有访问权限的
private:
    static int m_B;
};

int Person::m_A = 100; //需要强调是在Person作用域下
int Person::m_B = 200; //虽然是私有的,但是加了作用域,所以可以初始化!!!

void test01()
{
    Person p;
    // 100
    cout << p.m_A << endl;

    Person p2;
    p2.m_A = 200;

    // 100 ? 200
    cout << p.m_A << endl;
}

void test02()
{
    //静态成员变量,不属于某个对象上,所有对象共享一份数据
    //因此静态成员变量有两种访问方式

    // 1.通过对象进行访问
    Person p;
    cout << p.m_A << endl;
    // 2.通过类名进行访问
    cout << Person::m_A << endl;

    // cout << Person::m_B << endl; //类外访问不到这个私有的静态成员变量
}

int main()
{
    // test01();
    test02();

    return 0;
}
