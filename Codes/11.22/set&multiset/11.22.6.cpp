#include <iostream>
using namespace std;
#include <cstring>

// pair 对组 成对出现的数据，利用对组可以返回两个数据
/*
pair<type, type> p(value1, value2);
pair<type, type> p = make_pair(value1, value2);
*/

// paie对组
void test01()
{
    pair<string, int> p("Tom", 20);
    cout << "姓名: " << p.first << " 年龄: " << p.second << endl;

    pair<string, int> p2 = make_pair("Jerry", 10);
    cout << "姓名: " << p2.first << " 年龄: " << p2.second << endl;
}

int main()
{
    test01();

    return 0;
}
