#include <pthread.h>    // 实现多线程的头文件
#include <semaphore.h>  // 实现信号量定义的头文件
#include <unistd.h>

#include <fstream>
#include <iostream>

#define producerNumber 3  // 生产者的数目
#define consumerNumber 4  // 消费者的数目
#define M 5               // 缓冲区数目

#define MAXSIZE 1000
char consumeValue[MAXSIZE];  // 定义产品值的数组
static int Num = 0;

int in = 0;   // 生产者放置产品的位置
int out = 0;  // 消费者取产品的位置

int buff[M] = {0};  // 缓冲初始化为0， 开始时没有产品

sem_t empty_sem;        // 信号量的数据类型为结构sem_t，它本质上是一个长整型的数,同步信号量， 当满了时阻止生产者放产品
sem_t full_sem;         // 同步信号量， 当没产品时阻止消费者消费
pthread_mutex_t mutex;  // 互斥信号量， 一次只有一个线程访问缓冲

/* 打印缓冲情况 */
void print() {
    for (int i = 0; i < M; i++)
        std::cout << buff[i] << ' ';
    std::cout << std::endl;
}

void getData() {
    std::ifstream ifs;
    ifs.open("/mnt/d/Code/Code-C++/操作系统实验/2.txt", std::ios::in);

    if (ifs.is_open()) {
        ifs.read(consumeValue, sizeof(consumeValue));
    }
}

/* 生产者方法 */
void *product(void *arg) {
    int id = *(int *)arg + 1;
    while (true) {
        // 用sleep的数量可以调节生产和消费的速度，便于观察
        sleep(1);

        sem_wait(&empty_sem);        // 满不放
        pthread_mutex_lock(&mutex);  // 实现互斥

        in = in % M;
        buff[in] = rand() % 9 + 1;
        std::cout << "生产者" << id << "向" << in << "号缓冲区放入了一个数据" << buff[in] << ": \t";
        print();
        ++in;

        pthread_mutex_unlock(&mutex);
        sem_post(&full_sem);
    }
    return NULL;
}

/* 消费者方法 */
void *prochase(void *arg) {
    int id = *(int *)arg + 1;
    while (true) {
        sleep(1);

        sem_wait(&full_sem);         // 空不取
        pthread_mutex_lock(&mutex);  // 实现互斥

        out = out % M;
        std::cout << "消费者" << id << "向" << out << "号缓冲区取出一个数据" << buff[out] << ": \t";
        buff[out++] = 0;
        print();

        pthread_mutex_unlock(&mutex);
        sem_post(&empty_sem);
    }
    return NULL;
}

int main() {
    // 先得到数据
    getData();
    pthread_t id_producer[producerNumber];  // 声明生产者线程的ID数组
    pthread_t id_consumer[consumerNumber];  // 声明消费者线程的ID数组

    // 用来传入arg参数
    int arg_producer[producerNumber];
    int arg_consumer[consumerNumber];

    // 初始化同步信号量
    sem_init(&empty_sem, 0, M);
    sem_init(&full_sem, 0, 0);  // 同上初始化的描述

    // 初始化互斥信号量的函数
    pthread_mutex_init(&mutex, NULL);

    // 创建producerNumber个生产者线程
    for (int i = 0; i < producerNumber; ++i) {
        arg_producer[i] = i;
        pthread_create(&id_producer[i], NULL, product, (void *)&arg_producer[i]);
    }

    // 创建consumerNumber个消费者线程
    for (int i = 0; i < consumerNumber; ++i) {
        arg_consumer[i] = i;
        pthread_create(&id_consumer[i], NULL, prochase, (void *)&arg_consumer[i]);
    }

    // 销毁线程
    for (int i = 0; i < producerNumber; ++i)
        pthread_join(id_producer[i], NULL);
    // pthread_join()函数来使主线程阻塞以等待其他线程退出
    for (int i = 0; i < consumerNumber; ++i)
        pthread_join(id_consumer[i], NULL);

    exit(0);
}
