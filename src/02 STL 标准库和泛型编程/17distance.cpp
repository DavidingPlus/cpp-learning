#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include "17_Distance.h"

int main()
{
    // 求某个容器两个迭代器之间的距离
    vector<int> v{3, 5, 6, 7};
    cout << mydistance().Distance(v.begin(), v.end()) << endl; // 4
    list<int> l{3, 5, 6, 7, 12};
    cout << mydistance().Distance(l.begin(), l.end()) << endl; // 5

    return 0;
}