#include <iostream>
#include <thread>
#include <atomic>


std::atomic<bool> ready(false);


void count()
{
    // std::this_thread::yield()：暂时放弃线程的执行，将主动权交给其他线程（放心，主动权还会回来）。
    // 这里刻意这么设计，在主函数中就是为了让主线程先睡眠一段时间，改变 ready 条件以后，再执行子线程，刚好也测试了这个函数的用法。
    while (!ready) std::this_thread::yield();

    for (int i = 0; i <= 2000000000; i++)
        ;

    // std::this_thread::get_id()：获得当前线程 ID。
    std::cout << "Thread " << std::this_thread::get_id() << " finished!" << std::endl;


    return;
}


int main()
{
    constexpr int threadNum = 10;

    std::thread th[threadNum];

    for (int i = 0; i < threadNum; ++i) th[i] = std::thread(count);

    std::cout << "Main Thread is Sleeping!" << std::endl;

    // std::this_thread::sleep_for()：睡眠一段时间。
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    ready = true;

    std::cout << "Child Threads Start!" << std::endl;

    for (int i = 0; i < threadNum; ++i) th[i].join();


    return 0;
}
