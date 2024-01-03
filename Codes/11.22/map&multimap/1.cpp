#include <iostream>
using namespace std;
#include <map>

/*
**简介：**
* map中所有元素都是pair
* pair中第一个元素为key(键值)，起到索引作用，第二个元素为value（实值）
* 所有元素都会根据元素的键值自动排序

**本质：**
* map/multimap属于**关联式容器**，底层结构是用二叉树实现。

**优点：**
* 可以根据key值快速找到value值

map和multimap**区别**:(注意强调的是key值而不是value,value值可以相同!!!)
- map不允许容器中有重复key值元素
- multimap允许容器中有重复key值元素
*/

/*
map<T1, T2> mp;     // map默认构造函数:
map(const map &mp); //拷贝构造函数

赋值:
map &operator=(const map &mp); //重载等号操作符
*/

using Key = int;
using Value = int;
// map容器的构造和赋值
void printMap(const map<Key, Value> &m)
{
    for (map<Key, Value>::const_iterator iter = m.begin(); iter != m.end(); ++iter)
        cout << "key = " << iter->first << " value = " << iter->second << endl;
    cout << endl;
}

void test01()
{
    //创建map容器
    map<Key, Value> m;
    m.insert(pair<Key, Value>(1, 20));
    m.insert(pair<Key, Value>(4, 10));
    m.insert(pair<Key, Value>(3, 40));
    m.insert(pair<Key, Value>(2, 30));
    //会按照key来进行排序 默认升序
    printMap(m);

    //拷贝构造
    map<Key, Value> m2(m);
    printMap(m2);

    //赋值
    map<Key, Value> m3 = m2;
    printMap(m3);
}

void test02()
{
    //创建map容器
    map<Key, Value> m;
    //第一次插入
    pair<map<Key, Value>::iterator, bool> ret = m.insert(pair<Key, Value>(1, 20));
    if (ret.second)
        cout << "第一次插入成功" << endl;
    else
        cout << "第一次插入失败" << endl;

    ret = m.insert(pair<Key, Value>(1, 30));
    if (ret.second)
        cout << "第二次插入成功" << endl;
    else
        cout << "第二次插入失败" << endl;
}

int main()
{
    test01();
    test02();

    return 0;
}
