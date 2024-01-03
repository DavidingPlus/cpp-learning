#include <iostream>
using namespace std;
#include <cstring>

// string字符存取

/*
char &operator[](int n); //通过[]方式取字符
char &at(int n);         //通过at方法获取字符
*/

void test01()
{
    string str = "hello";
    cout << "str = " << str << endl;

    // 1.通过[]访问单个字符
    for (auto i = 0; i < str.size(); i++)
        cout << str[i] << ' ';
    cout << endl;
    // 2.通过at方式访问单个字符
    for (auto i = 0; i < str.size(); ++i)
        cout << str.at(i) << ' ';
    cout << endl;

    //修改单个字符
    str[0] = 'x';
    cout << "str = " << str << endl;

    str.at(1) = 'x';
    cout << "str = " << str << endl;
}

int main()
{
    test01();

    return 0;
}
