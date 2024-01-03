#include <iostream>
using namespace std;

//重载递增运算符

//自定义整型
class MyIntteger
{
    friend ostream &operator<<(ostream &cout, MyIntteger &myint);

public:
    MyIntteger() : m_Num(0) {}

    //重载前置++运算符
    MyIntteger &operator++()
    {
        //先进行++运算
        this->m_Num++;
        //再将自身做返回
        return *this;
    } //返回引用,因为如果返回值的话是创建一个新的对象,这里要保证一直对该对象进行操作,所以需要返回引用类型

    //重载后置++运算符
    //这个 int 代表占位参数,编译器通过这个可以用于区分前置和后置递增
    MyIntteger &operator++(int)
    {
        //先 记录当时的结果
        MyIntteger *temp = new MyIntteger(*this); //为了防止局部变量调用后被释放而无法使用引用,在堆区开辟数据!!!
        //后 递增
        this->m_Num++;
        //最后将记录结果返回
        return *temp;
    }

    int m_Num;
};

//重载左移运算符
ostream &operator<<(ostream &cout, MyIntteger &myint)
{
    cout << myint.m_Num;
    return cout;
}

void test01()
{
    MyIntteger myint;
    cout << ++myint << endl;
}

void test02()
{
    MyIntteger myint;
    cout << myint++ << endl;
    cout << myint << endl;
}

int main()
{
    // test01();
    test02();

    return 0;
}
