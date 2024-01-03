#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>

// adjacent_find(iterator beg, iterator end); 相邻重复元素!!!!
//  查找相邻重复元素,返回相邻元素的第一个位置的迭代器
//  beg 开始迭代器
//  end 结束迭代器

void test01()
{
    vector<int> v;
    v.push_back(0);
    v.push_back(2);
    v.push_back(0);
    v.push_back(3);
    v.push_back(1);
    v.push_back(4);
    v.push_back(3);
    v.push_back(3);

    //查找相邻重复元素
    auto pos = adjacent_find(v.begin(), v.end());
    if (pos == v.end())
        cout << "未找到相邻重复元素" << endl;
    else
        cout << "找到了相邻重复元素: " << *pos << endl;
}

int main()
{
    test01();

    return 0;
}
