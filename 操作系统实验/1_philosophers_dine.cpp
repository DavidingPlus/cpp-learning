#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

// 筷子作为mutex
static pthread_mutex_t chopstick[5];
// 定义哲学家数组
static pthread_t philosopher[5];

void *eat_think(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % 5;

    while (true)
    {
        sleep(1);                             // 思考
        pthread_mutex_lock(&chopstick[left]); // 拿起左手的筷子
        printf("Philosopher %d fetches chopstick %d\n", id, left);

        if (pthread_mutex_trylock(&chopstick[right]) == EBUSY) // EBUSY表示互斥锁锁定，无法获取当前对象
        // 无法拿起右手的筷子
        {
            pthread_mutex_unlock(&chopstick[left]); // 如果右边筷子被拿走放下左手的筷子
            // printf("Philosopher %d release chopstick %d\n", id, left);
            // continue;
        }

        // pthread_mutex_lock(&chopstick[right]); // 拿起右手的筷子，如果想观察死锁，/把上一句if的所有语句注释掉，再把这一句加上
        printf("Philosopher %d fetches chopstick %d\n", id, right);
        printf("Philosopher %d is eating.\n", id);
        sleep(1);                               // 吃饭
        pthread_mutex_unlock(&chopstick[left]); // 放下左手的筷子
        printf("Philosopher %d release chopstick %d\n", id, left);
        pthread_mutex_unlock(&chopstick[right]); // 放下右手的筷子
        printf("Philosopher %d release chopstick %d\n", id, right);
    }
    return NULL;
}

int main()
{
    int ids[5];
    // 初始化互斥锁
    for (int i = 0; i < 5; ++i)
        pthread_mutex_init(&chopstick[i], NULL);

    // 创建线程
    for (int i = 0; i < 5; ++i)
    {
        ids[i] = i;
        pthread_create(&philosopher[i], NULL, eat_think, &ids[i]);
    }

    // 挂起线程
    for (int i = 0; i < 5; ++i)
        pthread_join(philosopher[i], NULL);

    return 0;
}
