#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <exception>

int num = 100;
pthread_mutex_t mutex;

void *job(void *)
{
    // 加锁
    int res = pthread_mutex_lock(&mutex);
    std::cout << "lock res: " << res << '\n';

    // 重复加锁
    // trylock
    res = pthread_mutex_trylock(&mutex);
    std::cout << "trylock res: " << res << '\n';

    // lock
    res = pthread_mutex_lock(&mutex);
    std::cout << "lock res: " << res << '\n';
    if (EDEADLK == res)
    {
        throw std::runtime_error("double locking.");
    }

    for (int i = 0; i < 5; ++i)
    {
        std::cout << "num: " << num << '\n';
        sleep(1);
    }

    // 释放锁
    pthread_mutex_unlock(&mutex);

    return nullptr;
}

int main()
{
    // 初始化互斥锁
    pthread_mutex_init(&mutex, nullptr);

    // 检错锁，检测同一个线程多次请求同一把锁，其他行为和普通锁相同
    // pthread_mutexattr_t attr;
    // pthread_mutexattr_init(&attr);
    // pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    // pthread_mutex_init(&mutex, &attr);
    // pthread_mutexattr_destroy(&attr);

    // 创建子线程
    pthread_t tid;
    pthread_create(&tid, nullptr, job, nullptr);

    // 主线程回收资源
    pthread_join(tid, nullptr);

    pthread_mutex_destroy(&mutex);

    return 0;
}
