#include <iostream>
#include <thread>


void countNumber(int id, int n)
{
    for (int i = 1; i <= n; ++i)
        ;

    std::cout << "Thread " << id << " finished!" << std::endl;
}


int main()
{
    constexpr int threadNum = 10;

    std::thread th[threadNum];

    for (int i = 0; i < threadNum; i++) th[i] = std::thread(countNumber, i, 100000000);

    // thread 库中好像没有类似于 pthread_exit() 退出主线程并且不会影响其余线程的函数，这样就可以无脑 detach() 而不用考虑主线程执行完毕后结束进程的问题了。因此这里还是使用 join() 吧。
    for (int i = 0; i < threadNum; i++) th[i].join();


    return 0;
}
