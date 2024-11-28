#include <iostream>
using namespace std;
#include <list>
#include <algorithm>

void test()
{
    list<int> l{5, 2, 4, 3, 1};
    for (list<int>::iterator iter = l.begin(); iter != l.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;

    // 方法2
    for_each(l.begin(), l.end(), [&](int val)
             { cout << val << ' '; });
    cout << endl;
}

int main()
{
    test();

    return 0;
}