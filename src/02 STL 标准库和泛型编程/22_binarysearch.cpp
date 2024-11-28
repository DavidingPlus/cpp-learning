#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>

namespace Algorithm
{
    template <typename Container>
    void Sort(Container &con) // 传引用，不然不改变实参
    {
        sort(con.begin(), con.end());
    }

    template <typename Container>
    void rSort(Container &con) // 传引用，不然不改变实参
    {
        sort(con.rbegin(), con.rend());
    }

    template <typename Container>
    void print(Container &con) // 传引用，不然不改变实参
    {
        for (auto val : con)
            cout << val << ' ';
        cout << endl;
    }

    template <typename Random_Iterator, typename Value_Type>
    bool __Binary_Search(Random_Iterator first, Random_Iterator last, const Value_Type &val,
                         random_access_iterator_tag)
    {
        // 先做一个检查 val比 *first大 那么找不到
        if (val < *first)
            return false;

        while (first != last)
        {
            Random_Iterator mid = first + (last - first) / 2; // 没有两个迭代器相加的重载版本!!!!
            if (*mid > val)
                last = mid; // 注意last要满足前闭后开
            else if (*mid < val)
                first = ++mid;
            else
                return true;
        }
        return false;
    }

    template <typename Random_Iterator, typename Value_Type>
    bool __Binary_Search(Random_Iterator first, Random_Iterator last, const Value_Type &val,
                         random_access_iterator_tag, int) // 多一个int代表降序
    {
        // 先做一个检查 val比 *first大 那么找不到
        if (val > *first)
            return false;

        while (first != last)
        {
            Random_Iterator mid = first + (last - first) / 2; // 没有两个迭代器相加的重载版本!!!!
            if (*mid > val)
                first = ++mid;
            else if (*mid < val)
                last = mid; // 注意last要满足前闭后开
            else
                return true;
        }
        return false;
    }

    template <typename Iterator, typename Value_Type>
    // 写了一个random_access_iterator的重载
    bool Binary_Search(Iterator first, Iterator last, const Value_Type &val)
    {
        // 想办法让其可以适用于降序序列
        typename iterator_traits<Iterator>::iterator_category Iterator_Category; // 创建一个类型对象                                              // 升序 保持前闭后开的规则!!!
        return *first < *(last - 1) ? __Binary_Search(first, last, val, Iterator_Category)
                                    : __Binary_Search(first, last, val, Iterator_Category, true);
    }
}

int main()
{
    vector<int> v{1, 3, 6, 8, 7, 9, 2, 0};

    Algorithm::Sort(v); // 0 1 2 3 6 7 8 9
    Algorithm::print(v);
    cout << Algorithm::Binary_Search(v.begin(), v.end(), 2) << endl;
    // cout << binary_search(v.begin(), v.end(), 5) << endl;
    Algorithm::rSort(v);
    Algorithm::print(v);
    cout << Algorithm::Binary_Search(v.begin(), v.end(), 2) << endl;

    return 0;
}
