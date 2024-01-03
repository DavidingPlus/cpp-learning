#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>

// bool binary_search(iterator beg, iterator end, value);
//  查找指定的元素，查到 返回true  否则false
//  注意: 在**无序序列中不可用** !!!!!
//  beg 开始迭代器
//  end 结束迭代器
//  value 查找的元素

void printVector(const vector<int> &v)
{
    for (vector<int>::const_iterator iter = v.begin(); iter != v.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

bool myCompare(const int val1, const int val2)
{
    return val1 <= val2;
}

class myCompare_Pred
{
public:
    bool operator()(const int val1, const int val2) const { return val1 <= val2; }
};

void test01()
{
    vector<int> v;
    //插入一些无序数据
    v.push_back(1);
    v.push_back(4);
    v.push_back(6);
    v.push_back(3);
    v.push_back(8);
    v.push_back(2);
    v.push_back(0);
    v.push_back(9);
    v.push_back(5);
    v.push_back(7);
    //先打印
    printVector(v);
    //再进行排序 手动实现升序
    sort(v.begin(), v.end(), myCompare);
    // sort(v.begin(), v.end(), myCompare_Pred());
    printVector(v);

    //查找容器中是否有元素9
    //注意:容器必须是有序且升序的序列 不可以是降序!!!!!!
    bool ret = binary_search(v.begin(), v.end(), 9);
    if (ret)
        cout << "找到了元素" << endl;
    else
        cout << "未找到" << endl;
}

int main()
{
    test01();

    return 0;
}
