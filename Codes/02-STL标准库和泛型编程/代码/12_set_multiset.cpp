#include <iostream>
using namespace std;
#include <set>
#include <vector>

int main()
{
    vector<int> v{1, 3, 5, 4, 6, 8, 8, 9};
    for (int &val : v)
        ++val;
    for (int &val : v)
        cout << val << ' ';
    cout << endl;

    set<int, less<int>> s{1, 3, 5, 4, 6, 8, 8, 9};
    // for (int &val : s) // 这里就会报错,因为这个的迭代器是不可以更改值的
    //     ++val;
    for (int val : s)
        cout << val << ' ';
    cout << endl;

    return 0;
}
