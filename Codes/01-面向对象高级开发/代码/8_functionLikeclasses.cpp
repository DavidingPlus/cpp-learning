#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

// 函数指针作谓词
bool Cmp(int val1, int val2)
{
    return val1 <= val2;
}

// 函数对象(仿函数)作谓词
class Fuck
{
public:
    bool operator()(int val1, int val2) { return val1 <= val2; }
};

int main()
{
    vector<int> nums{5, 3, 4, 2, 1};
    // sort(nums.begin(), nums.end(), Cmp);
    sort(nums.begin(), nums.end(), Fuck());
    for_each(nums.begin(), nums.end(), [&](int val)
             { cout << val << ' '; });
    cout << endl;

    return 0;
}
