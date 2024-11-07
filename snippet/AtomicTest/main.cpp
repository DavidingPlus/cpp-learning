#include <iostream>
#include <thread>
#include <atomic>


// 将临界资源定义为线程级别的原子操作的数据。
// 即使是多线程，也要像同步进行一样同步操作 atomic 对象，从而省去了 mutex 上锁、解锁的时间消耗。故执行的更快。
std::atomic<int> n(0);


void count()
{
    for (int i = 0; i < 10000; ++i) ++n;
}


int main()
{
    std::thread th[100];

    for (auto &t : th) t = std::thread(count);

    for (auto &t : th) t.join();

    std::cout << n << std::endl;


    return 0;
}
