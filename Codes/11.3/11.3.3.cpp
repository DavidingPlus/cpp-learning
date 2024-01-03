#include <iostream>
using namespace std;

//菱形继承

//动物类
class Animal
{
public:
    int m_age;
};

//利用虚继承可以解决菱形继承的问题
//在继承之前加上关键字 virtual 变为虚继承
// Animal类称为 虚基类

//羊类
class Sheep : virtual public Animal
{
};

//驼类
class Tuo : virtual public Animal
{
};

//羊驼类
class SheepTuo : public Sheep, public Tuo
{
};

void test01()
{
    SheepTuo st;

    st.Sheep::m_age = 18;
    st.Tuo::m_age = 28;
    //当出现菱形继承的时候,两个父类拥有相同数据,需要加以作用域区分
    cout << "st.Sheep::m_age= " << st.Sheep::m_age << endl;
    cout << "st.Tuo::m_age= " << st.Tuo::m_age << endl;
    cout << "st.m_age= " << st.m_age << endl;

    //这份数据我们知道有一份就可以了,但是菱形继承导师数据有两份,资源浪费!
}

int main()
{
    test01();

    return 0;
}
