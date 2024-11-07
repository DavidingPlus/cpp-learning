#include <iostream>
#include <thread>
#include <mutex>


int n = 0;

std::mutex mtx;


void count()
{
    for (int i = 1; i <= 10000; i++)
    {
        mtx.lock();
        n++;
        mtx.unlock();
    }
}


int main()
{
    std::thread th[100];

    for (std::thread &t : th) t = std::thread(count);

    for (std::thread &t : th) t.join();

    std::cout << n << std::endl; // 加锁以后应该是 10000 * 100 == 1000000


    return 0;
}
