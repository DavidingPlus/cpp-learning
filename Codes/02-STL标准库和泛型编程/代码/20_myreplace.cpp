#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

template <typename Container>
void print(Container con)
{
    for (auto val : con)
        cout << val << ' ';
    cout << endl;
}

struct Algorithm
{
    template <class Iterator, class Value_Type>
    inline static void Replace(Iterator first, Iterator last, const Value_Type oldval, const Value_Type newval)
    {
        for (; first != last; ++first)
            if (*first == oldval)
                *first = newval;
    }

    template <class Iterator, class Value_Type, class Predicate>
    // 给一个谓词来判断条件是否更改
    inline static void Replace_if(Iterator first, Iterator last, Predicate pred, const Value_Type newval)
    {
        for (; first != last; ++first)
            if (pred(*first))
                *first = newval;
    }

    // 上面的算法当中传入的参数只有一个值，没传入比较的标准值
    // 为了解决这个问题需要引用仿函数适配器 functor adapter
    template <class Value_Type>
    bool operator()(const Value_Type &val)
    {
        return val > 5;
    }
};

int main()
{
    vector<int> v{1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print(v);

    Algorithm::Replace(v.begin(), v.end(), 1, 66);
    print(v);

    vector<int> v2{1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // Algorithm::Replace_if(v2.begin(), v2.end(), bind2nd(greater<int>(), 5), 666);
    Algorithm::Replace_if(v2.begin(), v2.end(), Algorithm(), 666);
    print(v2);

    vector<int> v3;
    v3.resize(v.size()); // 注意这里要给v3预分配空间，不然会段错误
    replace_copy(v.begin(), v.end(), v3.begin(), 10, 50);
    print(v3);

    return 0;
}
