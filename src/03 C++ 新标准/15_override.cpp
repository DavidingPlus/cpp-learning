#include <iostream>
using namespace std;

struct Base
{
    virtual void func(float) { cout << "Base func float" << endl; }
};

struct Derived1 : public Base
{
    // 第一个是定义了一个新的虚函数,不是override
    virtual void vfunc(int) { cout << "Derived1 func int" << endl; }
    // 第二个才是上面父类的override
    virtual void func(float) override { cout << "Derived1 func float" << endl; }
};

int main()
{
    Derived1().func(1.1);

    return 0;
}
