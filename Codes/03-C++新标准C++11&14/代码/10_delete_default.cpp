#include <iostream>
using namespace std;

// 如果已经定义了一个ctor，那么编译器就不会给一个默认的ctor
class Zoo
{
public:
    Zoo(int i1, int i2) : d1(i1), d2(i2) {}
    Zoo(const Zoo &) = delete; // delete表示我不要这一个重载
    Zoo(Zoo &&) = default;     // default表示我需要这一个重载并且是编译器默认提供给我的这个重载
    Zoo &operator=(const Zoo &) = default;
    Zoo &operator=(const Zoo &&) = delete;

    virtual ~Zoo() {}

private:
    int d1, d2;
};

int main()
{
    Zoo z1(1, 2);
    // Zoo z2(z1); // 无法使用因为他是已删除的函数

    return 0;
}