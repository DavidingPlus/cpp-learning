#include <iostream>
using namespace std;

auto Func(const int &val)
{
    return val > 0;
}

int main()
{
    // 注意函数指针的写法
    auto func = [](const int &val) -> bool
    {
        return val > 0;
    };
    bool (*func2)(const int &val) = Func;

    cout << func(1) << endl;
    cout << func2(-1) << endl;

    return 0;
}
