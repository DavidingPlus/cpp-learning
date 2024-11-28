#include <iostream>
using namespace std;

// Base1 鱼类 Derived1 鲫鱼
// Base2 鸟类 Derived2 麻雀
// 相应的有继承关系
class Base1
{
};
class Derived1 : public Base1
{
};

class Base2
{
};
class Derived2 : public Base2
{
};

// 现在定义一个pair类
template <class T1, class T2>
struct Pair
{
    T1 _first;
    T2 _second;
    Pair();
    Pair(const T1 &a, const T2 &b) : _first(a), _second(b) {}

    // 注意这里有一个Pair的拷贝赋值
    template <class U1, class U2>
    Pair(const Pair<U1, U2> &p) : _first(p._first), _second(p._second) {}
    // 这里怎么理解
    // 如果传入的类型是 T1 鱼类 T2 鸟类
    // 然后在调用拷贝赋值的时候传入的类型是 U1 鲫鱼 U2 麻雀
    // 显然 鲫鱼是鱼类 麻雀是鸟类 所以是可以传入的
    // 这个成员模板需要满足的条件就是 p._first这里是可以给自身的成员属性 _first 进行赋值的,在这里满足的是继承的关系
};

int main() { return 0; }