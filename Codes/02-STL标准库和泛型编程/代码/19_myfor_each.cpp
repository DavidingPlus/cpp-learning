#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

struct Algorithm
{
    template <class Iterator, class Function>
    inline static Function For_each(Iterator first, Iterator last, Function f)
    {
        for (; first != last; ++first)
            f(*first); // 注意是直接把数据传递给函数 f
        return f;
    }
};

int main()
{
    vector<int> v1{2, 5, 3, 6, 9};
    vector<int> v2;

    // 不修改v1的值
    Algorithm::For_each(v1.begin(), v1.end(), [&](int val)
                        { val*=2;v2.push_back(val); });

    for_each(v1.begin(), v1.end(), [&](auto val)
             { cout << val << ' '; });
    cout << endl;

    for (auto val : v2)
        cout << val << ' ';
    cout << endl;

    return 0;
}