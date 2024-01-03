#include <iostream>
using namespace std;
#include <map>

/*
insert(elem);    //在容器中插入元素。
clear();         //清除所有元素
erase(pos);      //删除pos迭代器所指的元素，返回下一个元素的迭代器。
erase(beg, end); //删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
erase(key);      //删除容器中值为key的元素。
*/

using Key = int;
using Value = int;

void printMap(const map<Key, Value> &m)
{
    for (auto iter = m.begin(); iter != m.end(); ++iter)
        cout << "key = " << iter->first << " value = " << iter->second << endl;
    cout << endl;
}

void test01()
{
    map<Key, Value> m;
    //第一种插入
    m.insert(pair<Key, Value>(1, 10));
    //第二种插入
    m.insert(make_pair(2, 20));
    //第三种插入
    m.insert(map<Key, Value>::value_type(3, 30));
    //第四种插入
    m[4] = 40;

    //不建议去插入 用途是利用key访问到value
    // cout << m[5] << endl;

    printMap(m);

    //删除
    m.erase(m.begin());
    printMap(m);

    m.erase(3);
    printMap(m);

    m.erase(30); //按照Key删除
    printMap(m);

    //清空
    // m.erase(m.begin(), m.end());
    m.clear();
    printMap(m);
}

int main()
{
    test01();

    return 0;
}
