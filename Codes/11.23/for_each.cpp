#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>

// for_each(iterator beg, iterator end, _func);
//  遍历算法 遍历容器元素
//  beg 开始迭代器
//  end 结束迭代器
//  _func 函数或者函数对象

//遍历常用算法 for_each
void print01(int val)
{
    cout << val << ' ';
}

class print02
{
public:
    void operator()(int val) { cout << val << ' '; }
};

void test01()
{
    vector<int> v;
    for (int i = 0; i < 10; ++i)
        v.push_back(i);

    //利用普通函数
    for_each(v.begin(), v.end(), print01);
    cout << endl;

    //利用函数对象(仿函数)
    for_each(v.begin(), v.end(), print02());
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
