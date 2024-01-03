#include <iostream>
using namespace std;
#include <set>

/*
find(key);  //查找key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
count(key); //统计key的元素个数
*/

//查找
void test01()
{
    set<int> s1;
    //插入
    s1.insert(10);
    s1.insert(30);
    s1.insert(20);
    s1.insert(40);

    //查找
    set<int>::iterator iter = s1.find(30);
    if (iter != s1.end())
        cout << "找到元素: " << *iter << endl;
    else
        cout << "未找到元素" << endl;
}

//统计
void test02()
{
    set<int> s1;
    //插入
    s1.insert(10);
    s1.insert(10);
    s1.insert(30);
    s1.insert(30);
    s1.insert(30);
    s1.insert(20);
    s1.insert(40);

    //统计
    int num1 = s1.count(30);
    //对于set而言,统计的结果要么是0要么是1
    cout << "num1 = " << num1 << endl;

    multiset<int> s2;
    //插入
    s2.insert(10);
    s2.insert(10);
    s2.insert(30);
    s2.insert(30);
    s2.insert(30);
    s2.insert(20);
    s2.insert(40);

    //统计
    int num2 = s2.count(30);
    cout << "num2 = " << num2 << endl;
}

int main()
{
    // test01();
    test02();

    return 0;
}
