#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

//求两个集合的差集
//函数原型::

// set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
//  求两个集合的差集
//  **注意:两个集合必须是有序序列**
//  beg1 容器1开始迭代器
//  end1 容器1结束迭代器
//  beg2 容器2开始迭代器
//  end2 容器2结束迭代器
//  dest 目标容器开始迭代器

void myPrint(const int val)
{
    cout << val << ' ';
}

void test01()
{
    vector<int> v1;
    vector<int> v2;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 5);
    }

    //给出一个目标容器接受
    vector<int> target;
    //为target预留相应空间(因为我们也不知道是多少个,只有用容量来刻画)
    int capacity = v1.size() >= v2.size() ? v1.size() : v2.size();
    target.reserve(capacity);
    //返回目标容器最后一个迭代器的地址 获取交集
    //注意:两个集合必须是有序序列且升序序列!!!!!!
    cout << "v1与v2的差集为:  " << endl;
    vector<int>::iterator target_end =
        set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), target.begin());
    for_each(target.begin(), target_end, myPrint);
    cout << endl;

    cout << "v2与v1的差集为:  " << endl;
    target_end = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), target.begin());
    for_each(target.begin(), target_end, myPrint);
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
