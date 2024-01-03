#include <iostream>
using namespace std;
#include <cstring>

//字符串求字串
// string substr(int pos = 0, int n = npos) const; //返回由pos开始的n个字符组成的字符串

void test01()
{
    string str = "abcdef";
    string substr = str.substr(1, 3);
    // bcd
    cout << "substr = " << substr << endl;
}

//实用操作
void test02()
{
    string email = "zhangsan@sina.com";

    //从邮件中地址中获取用户名的信息
    int pos = email.find("@");
    string usrname = email.substr(0, pos);
    cout << "usrname = " << usrname << endl;
}

int main()
{
    // test01();
    test02();

    return 0;
}
