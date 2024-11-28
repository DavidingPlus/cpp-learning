#include <iostream>
using namespace std;

class Foo
{
public:
    // ctor
    Foo(int i) : _i(i) {}
    Foo() = default;

    // copy ctor
    Foo(const Foo &x) : _i(x._i) {}
    // Foo(const Foo &) = default; // error 都已经定义出来了还要默认的，不行
    // Foo(const Foo &) = delete;  // error 都已经定义出来又不要了，不行

    // copy assign
    Foo &operator=(const Foo &x)
    {
        _i = x._i;
        return *this;
    }

    // Foo &operator=(const Foo &x) = default; // error 都已经定义出来了还要默认的，不行
    // Foo &operator=(const Foo &x) = delete;  // error 都已经定义出来又不要了，不行

    // void func1() = default; // error 一般的函数没有默认版本，只能用于 big five上面
    void func2() = delete; // delete可以用在任何函数上面(=0 只能用于 virtual 函数)

    // ~Foo() = delete;//error 不能删除析构函数，这会导致使用Foo对象错误!!!!
    ~Foo() = default;

private:
    int _i;
};

int main()
{
    Foo f1; // 如果不写 Foo() = default 编译器不会提供默认构造函数，会报错
    Foo f2(5);
    Foo f3(f1);
    f3 = f2;

    return 0;
}
