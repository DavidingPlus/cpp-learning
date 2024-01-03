#include <iostream>
using namespace std;

//左移运算符重载

class Person
{
    friend ostream &operator<<(ostream &cout, Person &p);

public:
    Person(int a, int b) : m_A(a), m_B(b) {}

private:
    //利用成员函数来重载 左移运算符 p.operator<<(cout) 简化版本 p << cout
    //不会利用成员函数重载 << 运算符,因为无法实现cout在左侧
    // void operator<<(cout)
    // {
    // }

    int m_A;
    int m_B;
};

//只能利用全局函数重载左移运算符
ostream &operator<<(ostream &cout, Person &p) //本质 operator << (cout , p) 简化形式 cout << p
// cout是属于ostream(标准输出流对象)里面,全局只有一个,所以用引用传入!!!!
{
    cout << "m_A= " << p.m_A << endl
         << "m_B= " << p.m_B << endl;
    return cout;
}

void test01()
{
    Person p(10, 10);

    cout << p << "hello world! " << endl;
}

int main()
{
    test01();

    return 0;
}
