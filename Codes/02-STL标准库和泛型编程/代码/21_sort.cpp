#include <iostream>
using namespace std;
#include <vector>
#include <array>
#include <algorithm>
#include <bits/stl_function.h>

template <typename Container>
void print(Container con)
{
    for (auto val : con)
        cout << val << ' ';
    cout << endl;
}

bool myfunc(int i, int j)
{
    return i < j;
}

template <class Value_Type>
// 继承了这个关系之后后面就可以通过适配器对其进行改造!!!
struct myclass : public binary_function<Value_Type, Value_Type, Value_Type>
{
    bool operator()(Value_Type i, Value_Type j) { return i < j; }
};

int main()
{
    array<int, 8> arr = {32, 71, 12, 45, 26, 80, 53, 33};
    vector<int> v(arr.begin(), arr.end());
    print(v);

    // using default comparison (operator <)
    sort(v.begin(), v.begin() + 4); // 排序前四个 12 32 45 71 26 80 53 33
    print(v);

    // using function as comp
    sort(v.begin() + 4, v.end(), myfunc); // 12 32 45 71 26 33 53 80
    print(v);

    // using object as comp
    sort(v.begin(), v.end(), myclass<int>()); // 12 26 32 33 45 53 71 80
    print(v);

    // reverse iterators
    sort(v.rbegin(), v.rend(), less<int>()); // 80 71 53 45 33 32 26 12
    print(v);

    return 0;
}
