#include <iostream>
using namespace std;
#include <map>

/*
find(key);  //查找key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
count(key); //统计key的元素个数
*/

// map容器 查找和统计
using Key = int;
using Value = int;

//查找
void test01()
{
    //查找
    map<Key, Value> m;
    m.insert(make_pair(1, 10));
    m.insert(make_pair(2, 20));
    m.insert(make_pair(3, 30));
    m.insert(make_pair(3, 40));

    map<Key, Value>::iterator pos = m.find(3);
    if (pos != m.end())
        cout << "查到了元素 Key = " << pos->first << " value = " << pos->second << endl;
    else
        cout << "未查到元素" << endl;

    //统计
    // map容器中不允许插入重复Key元素 count统计而言要么是0 要么是1
    // multimap的count统计可能大于1
    size_t num = m.count(3);
    cout << "num = " << num << endl;
}

int main()
{
    test01();

    return 0;
}
