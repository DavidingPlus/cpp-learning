#include <iostream>
#include <pthread.h>

void test1();

void test2();
void *job(void *);
int num = 100;
pthread_rwlock_t rwlock;

int main()
{
    // test1();
    test2();

    return 0;
}

void test1()
{
    // 动态初始化
    // pthread_rwlock_t rwlock;
    // pthread_rwlock_init(&rwlock, nullptr);

    // 静态初始化
    pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

    // 销毁
    // 对于静态初始化，不推荐手动销毁，因为可能造成不可预测的运行时问题
    // pthread_rwlock_destroy(&rwlock);
}

void *job(void *)
{
    // 加读锁
    int res = pthread_rwlock_rdlock(&rwlock);
    std::cout << res << '\n';

    // 加入读锁之后不释放的情况下加入写锁，看会发生什么
    res = pthread_rwlock_wrlock(&rwlock); // 阻塞
    std::cout << res << '\n';

    // 释放锁
    // 思考一下为什么加锁有两个，解锁却只有一个？
    pthread_rwlock_unlock(&rwlock);

    return nullptr;
}

void test2()
{
    pthread_rwlock_init(&rwlock, nullptr);

    pthread_t tid;
    pthread_create(&tid, nullptr, job, nullptr);
    pthread_join(tid, nullptr);

    pthread_rwlock_destroy(&rwlock);
}
