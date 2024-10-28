#include <iostream>
#include <future>
#include <string>


int main()
{
    // 不同于 std::thread，std::async 是一个函数，所以没有成员函数。
    // std::launch 有 2 个枚举值和 1 个特殊值：
    // std::launch::async	    0x1（1）	                    异步启动
    // std::launch::deferred	0x2（2）	                    在调用 future::get、future::wait 时同步启动
    // std::launch::async | std::launch::defereed	0x3（3）	同步或异步，根据操作系统而定

    auto f = std::async(
        std::launch::async,

        [](const std::string &message)
        { std::cout << message << std::flush; },

        "Hello, ");

    std::cout << "World!" << std::endl;

    return 0;
}
