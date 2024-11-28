#include <iostream>
#include <pthread.h>
#include <unistd.h>

void *job1(void *args)
{
    pthread_key_t key = *(pthread_key_t *)args;

    // 设置值
    int num1 = 1;
    pthread_setspecific(key, (void *)&num1);

    // 获取值，一键多值
    void *res = pthread_getspecific(key);
    std::cout << "thread1: " << *(int *)res << '\n';

    return nullptr;
}

void *job2(void *args)
{
    pthread_key_t key = *(pthread_key_t *)args;

    sleep(1);

    int num2 = 2;
    pthread_setspecific(key, (void *)&num2);

    void *res = pthread_getspecific(key);
    std::cout << "thread2: " << *(int *)res << '\n';

    return nullptr;
}

int main()
{
    pthread_t tid1, tid2;
    pthread_key_t key;

    pthread_key_create(&key, nullptr);

    pthread_create(&tid1, nullptr, job1, (void *)&key);
    pthread_create(&tid2, nullptr, job2, (void *)&key);

    pthread_detach(tid1);
    pthread_detach(tid2);

    pthread_exit(nullptr);

    return 0;
}
