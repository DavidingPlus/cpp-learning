#include <iostream>
using namespace std;

struct Nocopy
{
    Nocopy() = default;
    Nocopy(const Nocopy &) = delete;            // no copy
    Nocopy &operator=(const Nocopy &) = delete; // no assign
    ~Nocopy() = default;
};

struct NoDtor
{
    NoDtor() = default;
    ~NoDtor() = delete; // 非常不建议这么去做
};

void testNoDtor()
{
    // NoDtor nd;//栈区对象的生命周期在这个函数结束就销毁了，这时候会自动调用dtor，没有则报错
    NoDtor *p = new NoDtor; // 动态开辟是允许的，但是无法销毁
    // delete p;               // 不允许销毁
}

class PrivateCopy
{
private:
    // 这个类无法被一般的代码调用，但是可以被friend和member调用copy
    // 如果要禁止，不仅需要放到private里面，还要加上 = delete
    PrivateCopy(const PrivateCopy &);
    PrivateCopy &operator=(const PrivateCopy &);

public:
    PrivateCopy() = default;
    ~PrivateCopy();
};

int main()
{
    testNoDtor();

    return 0;
}
