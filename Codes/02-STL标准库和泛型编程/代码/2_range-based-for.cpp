#include <iostream>
using namespace std;
#include <vector>

// 遍历vector容器
template <typename Type>
void print(vector<Type> container)
{
    for (auto elem : container)
        cout << elem << ' ';
    cout << endl;
}

int main()
{
    print(vector<int>{1, 5, 6, 9, 7, 5, 3, 10});

    vector<double> nums{1.1, 2.5, 6.33, 15.66, 1.44, 2.52};
    print(nums);

    // 稍微修改一下
    for (auto &elem : nums)
        elem -= 1; // 减一
    print(nums);

    return 0;
}
