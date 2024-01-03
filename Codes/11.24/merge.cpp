#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

// merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
//  容器元素合并，并存储到另一容器中
//  注意: 两个容器必须是**有序并且同为升序的**
//  beg1   容器1开始迭代器
//  end1   容器1结束迭代器
//  beg2   容器2开始迭代器
//  end2   容器2结束迭代器
//  dest   目标容器开始迭代器

//常用排序算法 merge
class myPrint_Pred
{
public:
    void operator()(const int val) const { cout << val << ' '; }
};

void test01()
{
    vector<int> v1;
    vector<int> v2;
    for (int i = 0; i < 10; ++i)
    {
        v1.push_back(i);
        v2.push_back(i + 1);
    }

    //目标容器
    vector<int> target;
    //提前给target容器开辟空间
    target.resize(v1.size() + v2.size());
    // merge算法 两个容器必须是同时是有序且为升序的!!!!
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), target.begin());
    for_each(target.begin(), target.end(), myPrint_Pred());
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
