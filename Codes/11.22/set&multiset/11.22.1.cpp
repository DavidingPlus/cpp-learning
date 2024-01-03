#include <iostream>
using namespace std;
#include <set>

/*
简介:
所有元素都会在插入时自动被排序!!!

本质:
set/multiset属于**关联式容器**，底层结构是用**二叉树**实现。

set和multiset区别:
set不允许容器中有重复的元素
multiset允许容器中有重复的元素
*/

/*
构造：
set<T> st;          //默认构造函数：
set(const set &st); //拷贝构造函数

赋值：
set &operator=(const set &st); //重载等号操作符
*/

void printSet(const set<int> &s)
{
    for (set<int>::const_iterator iter = s.begin(); iter != s.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

// set容器构造和赋值
void test01()
{
    set<int> s1;
    //插入数据 只有insert方式
    s1.insert(20);
    s1.insert(30);
    s1.insert(30);
    s1.insert(40);
    s1.insert(50);
    s1.insert(10);
    //在插入的时候会被自动排序(默认升序)并且不允许插入重复的数据,如果有将不会插入进去!!!
    //遍历容器 10 20 30 40 50
    printSet(s1);

    //拷贝构造
    set<int> s2(s1);
    printSet(s2);

    //赋值操作
    set<int> s3 = s2;
    printSet(s3);
}

int main()
{
    test01();

    return 0;
}
