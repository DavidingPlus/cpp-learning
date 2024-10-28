#include <iostream>
#include <future>
#include <chrono>


void countNumber()
{
    for (int i = 0; i < 1e9; ++i)
        ;
}


int main()
{
    // 特化的 std::future<void>。
    // std::future 的作用并不只有获取返回值，它还可以检测线程是否已结束、阻塞等待，所以对于返回值是 void 的线程来说，std::future 也同样重要。
    std::future<void> f = std::async(
        std::launch::async,

        countNumber);

    std::cout << "Please wait" << std::flush;

    // std::future<> 的成员函数：
    // get()：获取返回值。
    // wait()：阻塞等待线程结束，返回值为 void。
    // wait_for()：阻塞等待一段时间。若在这段时间内线程结束则返回 future_status::ready；若没结束则返回 future_status::timeout；若 std::async 是以 std::launch::deferred 启动的，则不会阻塞并立即返回 future_status::deferred。

    while (f.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) std::cout << '.' << std::flush;

    std::cout << std::endl
              << "Finished!" << std::endl;


    return 0;
}
