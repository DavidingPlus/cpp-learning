#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>

// transform(iterator beg1, iterator end1, iterator beg2, _func);
// beg1 源容器开始迭代器
// end1 源容器结束迭代器
// beg2 目标容器开始迭代器
//_func 函数或者函数对象

//常用遍历算法 transform
class Transform
{
public:
    int operator()(int val) { return val; }
};

class Print
{
public:
    void operator()(int val) { cout << val << ' '; }
};

void test01()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);
    for_each(v.begin(), v.end(), Print());
    cout << endl;

    vector<int> target;
    target.resize(v.size()); //目标容器必须提前开辟空间
    //最后的这个参数是一个函数对象(仿函数),必须有,是对搬运的数据进行操作,不需要直接返回就行(必须写)
    transform(v.begin(), v.end(), target.begin(), Transform());
    for_each(target.begin(), target.end(), Print());
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
