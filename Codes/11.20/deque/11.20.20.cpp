#include <iostream>
using namespace std;
#include <deque>

// deque赋值操作

/*
deque &operator=(const deque &deq); //重载等号操作符
assign(beg, end);                   //将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);                    //将n个elem拷贝赋值给本身。
*/

void printDeque(const deque<int> &d)
{
    for (deque<int>::const_iterator iter = d.begin(); iter < d.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

void test01()
{
    deque<int> d1;
    for (auto i = 0; i < 10; ++i)
        d1.push_back(i);
    printDeque(d1);

    // operator= 赋值
    deque<int> d2 = d1;
    printDeque(d2);

    // assgin
    deque<int> d3;
    d3.assign(d1.begin(), d1.end());
    printDeque(d3);

    // n个elem
    deque<int> d4;
    d4.assign(10, 100);
    printDeque(d4);
}

int main()
{
    test01();

    return 0;
}
