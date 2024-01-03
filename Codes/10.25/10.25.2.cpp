#include <iostream>
using namespace std;

//深拷贝与浅拷贝
class Person
{
public:
    Person()
    {
        cout << "Person的默认构造函数调用" << endl;
    }

    Person(int age, int height)
    {
        m_Height = new int(height);
        m_age = age;
        cout << "Person的有参构造函数调用" << endl;
    }

    //自己实现一个拷贝构造函数 解决浅拷贝带来的问题
    Person(const Person &p)
    {
        cout << "Person的拷贝构造函数调用" << endl;
        m_age = p.m_age;
        // m_Height=p.m_Height; //编译器默认实现就是这行代码
        //这是浅拷贝,p1,p2在释放时由于指向同一个空间,会被释放两次,会出现错误!!!

        //深拷贝操作 让他指向另一个堆区空间
        m_Height = new int(*p.m_Height);
    }

    ~Person()
    {
        //析构代码,将堆区开辟数据做释放操作
        if (m_Height)
        {
            delete m_Height;
            m_Height = nullptr;
        }

        cout << "Person的析构函数调用" << endl;
    }

    int m_age;     //年龄
    int *m_Height; //身高
};

void test01()
{
    Person p1(18, 160);
    cout << "p1的年龄为: " << p1.m_age << " 身高为: " << *p1.m_Height << endl;

    Person p2(p1);
    cout << "p2的年龄为: " << p2.m_age << " 身高为: " << *p2.m_Height << endl;
}

//如果属性又在堆区开辟的,一定要自己提供拷贝构造函数,防止浅拷贝带来的问题
int main()
{
    test01();

    return 0;
}
