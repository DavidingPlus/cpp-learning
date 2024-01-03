#include <iostream>
using namespace std;

//三种继承方式 公有继承 保护继承 私有继承
//父类中的私有权限 不管哪一种继承方式都无法访问!!!
//公有继承: 子类中public和protected权限各自都不变
//保护继承: 子类中public和protected权限都变为protected
//私有继承: 子类中public和protected权限都变为private

//公共权限 public    成员 类内可以访问 类外可以访问
//保护权限 protected 成员 类内可以访问 类外不可以访问 儿子可以访问父亲中的保护内容
//私有权限 private   成员 类内可以访问 类外不可以访问 儿子不可以访问父亲的私有内容

//继承方式

//公共继承
class Base
{
public:
    int m_A;

protected:
    int m_B;

private:
    int m_C;
};

class Son1 : public Base
{
public:
    void func()
    {
        m_A = 10; //父类中的公共权限成员 到子类中依然是公共权限
        m_B = 10; //父类中的保护权限成员 到子类中依然是保护权限
        // m_C = 10; //父类中的私有权限成员 子类访问不到
    }
};

class Son2 : protected Base
{
public:
    void func()
    {
        m_A = 10; //父类中的公共权限成员 到子类中变为保护权限
        m_B = 10; //父类中的保护权限成员 到子类中变为保护权限
        // m_C = 10; //父类中的私有权限成员 子类访问不到
    }
};

class Son3 : private Base
{
public:
    void func()
    {
        m_A = 10; //父类中的公共权限成员 到子类中变为私有权限 但在类内子类能访问!!!(与m_C区别!!!)
        m_B = 10; //父类中的保护权限成员 到子类中变为私有权限
        // m_C = 10; //父类中的私有权限成员 子类访问不到
    }
};

class GrandSon3 : public Son3
{
public:
    void func()
    {
        // m_A = 1000;//到了Son3中 m_A变为私有 即使是儿子 也访问不到
        // m_B = 1000;//到了Son3中 m_B变为私有 即使是儿子 也访问不到
    }
};

void test01()
{
    Son1 s1;
    s1.m_A = 100;
    // s1.m_B = 100;//到了Son1中 m_B是保护权限 类外访问不到
}

void test02()
{
    Son2 s2;
    // s2.m_A = 100; //在Son2中 m_A变为保护权限 类外访问不到
    // s2.m_B = 100; //在Son2中 m_B保护权限 类外访问不到
}

void test03()
{
    Son3 s3;
    // s3.m_A = 100; //在Son3中 m_A变为私有权限 类外访问不到
    // s3.m_B = 100; //在Son3中 m_B变为私有权限 类外访问不到
}

int main()
{

    return 0;
}
