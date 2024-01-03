#include <iostream>
using namespace std;
#include <map>

//利用仿函数，可以改变排序规则
using Key = int;
using Value = int;

class myCompare
{
public:
    bool operator()(const Key &key1, const Key &key2) const
    {
        return key1 > key2;
    }
};

void test01()
{
    //默认从小到大排序
    //利用仿函数实现从大到小排序
    map<Key, Value, myCompare> m;

    m.insert(make_pair(1, 20));
    m.insert(make_pair(2, 40));
    m.insert(make_pair(3, 50));
    m.insert(make_pair(4, 60));
    m.insert(make_pair(5, 10));

    for (map<Key, Value, myCompare>::iterator iter = m.begin(); iter != m.end(); ++iter)
        cout << "key:" << iter->first << " value:" << iter->second << endl;
}

int main()
{
    test01();

    return 0;
}
