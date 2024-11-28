#include <iostream>
using namespace std;
#include <map>

int main()
{

    // 第一个参数是key(不可修改,所以进去后红黑树会自动转为const类型),第二个参数是data
    map<int, char, less<int>> m{make_pair(9, 'a'),
                                make_pair(5, 'b'),
                                make_pair(6, 'c'),
                                make_pair(4, 'd'),
                                make_pair(8, 'c'),
                                make_pair(9, 'b'),
                                make_pair(6, 'd'),
                                make_pair(1, 'a')};
    m[0] = 'f';
    for (auto &val : m)
    {
        cout << val.first << ' ' << m[val.first] << endl;
        val.second++;
        cout << val.first << ' ' << val.second << endl;
    }

    return 0;
}
