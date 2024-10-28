#include <iostream>
#include <thread>
#include <future>

#include "sum.h"


template <class... Args>
void doIt(std::promise<int> &p, Args &&...args)
{
    // 成员函数 set_value()
    // 设置 promise 的值并将 future_status 设为 ready。
    // void 特化：只将共享状态设为 ready。
    p.set_value(sum(args...));
}


int main()
{
    // std::promise 本质上是 std::future 的一个包装。std::future的值不能被改变，但可以通过 std::promise 来创建一个拥有特定值的 std::future。
    // std::promise 的原理就是不改变已有 std::future 的值，而是创建新的 std::future 对象。

    std::promise<int> p;

    std::thread t(doIt<int, int, int>, std::ref(p), 1, 10, 100);

    t.join();

    // 成员函数 get_future()
    // 构造一个 std::future 对象，其值与 std::promise 相同，status 也与 promise 相同。
    std::cout << p.get_future().get() << std::endl;


    return 0;
}
