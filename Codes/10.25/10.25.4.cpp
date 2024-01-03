#include <iostream>
#include <string.h>
using namespace std;

//类对象作为类成员
//手机类
class Phone
{
public:
    Phone(string PName) : m_PName(PName)
    {
        cout << "Phone构造函数的调用" << endl;
    } //用初始化列表进行初始化

    ~Phone()
    {
        cout << "Phone析构函数的调用" << endl;
    }
    //手机品牌名称
    string m_PName;
};

class Person
{
public:
    // Phone m_Phone=PName 隐式转换法
    Person(string Name, string PName) : m_Name(Name), m_Phone(PName)
    {
        cout << "Person构造函数的调用" << endl;
    }

    ~Person()
    {
        cout << "Person析构函数的调用" << endl;
    }
    //姓名
    string m_Name;
    //手机
    Phone m_Phone;
};

//当其他类的对象作为本类成员,构造时候先构造类对象,再构造自身
//析构的顺序与构造相反!!!!!
void test01()
{
    Person p("张三", "IPhone Max");
    cout << p.m_Name << "拿着: " << p.m_Phone.m_PName << endl;
}

int main()
{
    test01();

    return 0;
}
