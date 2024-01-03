#include <iostream>
using namespace std;
#include <deque>
#include <algorithm> //标准算法头文件

// deque容器排序

// sort(iterator beg, iterator end) //对beg和end区间内元素进行排序

void printDeque(const deque<int> &d)
{
    for (deque<int>::const_iterator iter = d.begin(); iter < d.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

void test01()
{
    deque<int> d;
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    d.push_front(100);
    d.push_front(200);
    d.push_front(300);

    // 300 200 100 10 20 30
    printDeque(d);
    // sort
    sort(d.begin(), d.end()); //引头文件 algorithm
    printDeque(d);
}

int main()
{
    test01();

    return 0;
}
