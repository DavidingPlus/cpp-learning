#include <iostream>
#include <pthread.h>

int main()
{
    // 动态初始化
    // pthread_rwlock_t rwlock;
    // pthread_rwlock_init(&rwlock, nullptr);

    // 静态初始化
    pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

    // 销毁
    // pthread_rwlock_destroy(&rwlock); // 对于静态初始化，不推荐手动销毁，因为可能造成不可预测的运行时问题

    return 0;
}
