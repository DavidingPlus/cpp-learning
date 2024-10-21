#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <assert.h>
#include <iostream>


#define num 100
#define thread_num 3


int data[num];        // 待排序数据
int thread_unit = 10; // 每个任务处理10个数据


typedef struct worker
{
    void *(*process)(void *arg); /*该任务需要调用的函数*/
    void *arg;                   /*该任务需要的参数*/
    struct worker *next;
} task;


/*线程池结构*/
typedef struct
{
    pthread_mutex_t queue_lock; // 线程池的互斥变量
    pthread_cond_t queue_ready; // 线程池的条件变量
    task *queue_head;           /*链表结构，线程池中所有等待任务*/
    int shutdown;               /*是否销毁线程池*/
    pthread_t *threadid;        // 线程ID的指针
    int max_thread_num;         /*线程池中允许的活动线程数目*/
    int cur_queue_size;         /*当前等待队列的任务数目*/
} thread_pool;


int add_task(void *(*process)(void *arg), void *arg);
void *thread_routine(void *arg);


static thread_pool *pool = NULL; // 刚开始指针为空


void pool_init(int max_thread_num)
{
    pool = (thread_pool *)malloc(sizeof(thread_pool));
    pthread_mutex_init(&(pool->queue_lock), NULL);
    pthread_cond_init(&(pool->queue_ready), NULL);
    pool->queue_head = NULL;
    pool->max_thread_num = max_thread_num;
    pool->cur_queue_size = 0;
    pool->shutdown = 0;
    pool->threadid = (pthread_t *)malloc(max_thread_num * sizeof(pthread_t));
    int i = 0;
    for (i = 0; i < max_thread_num; i++)
    {
        pthread_create(&(pool->threadid[i]), NULL, thread_routine, NULL); // 创建线程
    }
}

int add_task(void *(*process)(void *arg), void *arg)
{                                                   /*向线程池中加入任务*/
    task *newworker = (task *)malloc(sizeof(task)); /*构造一个新任务*/
    newworker->process = process;
    newworker->arg = arg;
    newworker->next = NULL;
    pthread_mutex_lock(&(pool->queue_lock)); // 向任务队列中添加任务是互斥操作要上锁
    task *member = pool->queue_head;
    if (member != NULL)
    {
        while (member->next != NULL)
            member = member->next;
        member->next = newworker;
    }
    else
    {
        pool->queue_head = newworker; // 尾插法
    }
    assert(pool->queue_head != NULL);
    pool->cur_queue_size++;
    pthread_mutex_unlock(&(pool->queue_lock));
    pthread_cond_signal(&(pool->queue_ready)); /*条件已满足，向等待这个条件的线程发出信号，唤醒休眠的进程*/
    return 0;
}

int pool_destroy()
{
    if (pool->shutdown) return -1; /*防止两次调用*/
    pool->shutdown = 1;
    /*唤醒所有等待线程，线程池要销毁了*/
    pthread_cond_broadcast(&(pool->queue_ready));
    int i;
    for (i = 0; i < pool->max_thread_num; i++) pthread_join(pool->threadid[i], NULL); // 所有线程结束
    free(pool->threadid);
    /*销毁等待队列*/
    task *head = NULL;
    while (pool->queue_head != NULL)
    {
        head = pool->queue_head;
        pool->queue_head = pool->queue_head->next;
        free(head);
    }
    /*条件变量和互斥量也别忘了销毁*/
    pthread_mutex_destroy(&(pool->queue_lock));
    pthread_cond_destroy(&(pool->queue_ready));
    free(pool);
    /*销毁后指针置空是个好习惯*/
    pool = NULL;
    return 0;
}

void *thread_routine(void *arg)
{
    printf("starting thread 0x%lx\n", pthread_self());
    while (1)
    {
        pthread_mutex_lock(&(pool->queue_lock));
        while (pool->cur_queue_size == 0 && !pool->shutdown)
        { /*如果等待队列为0并且不销毁线程池，则处于阻塞状态; 注意pthread_cond_wait是一个原子操作，等待前会解锁，唤醒后会加锁*/
            printf("thread 0x%lx is waiting\n", pthread_self());
            pthread_cond_wait(&(pool->queue_ready), &(pool->queue_lock)); // 线程进行等待状态，同时解锁
        }
        /*线程池要销毁了*/
        if (pool->shutdown)
        {
            /*遇到break,continue,return等跳转语句，千万不要忘记先解锁*/
            pthread_mutex_unlock(&(pool->queue_lock));
            printf("thread 0x%lx will exit\n", pthread_self());
            pthread_exit(NULL);
        }
        printf("thread 0x%lx is starting to work\n", pthread_self());
        assert(pool->cur_queue_size != 0); // 任务队列不为空
        assert(pool->queue_head != NULL);  //
        /*等待队列长度减去1，并取出链表中的头元素*/
        pool->cur_queue_size--;
        task *worker = pool->queue_head;
        pool->queue_head = worker->next;
        pthread_mutex_unlock(&(pool->queue_lock));
        (*(worker->process))(worker->arg); /*调用排序函数函数开始执行任务*/
        free(worker);
        worker = NULL;
        sleep(1);
    }
    std::cout << "excute here!" << std::endl;
    pthread_exit(NULL);
}

void heapsort(int begin)
{ // 将每一段进行排序
    int start = begin * thread_unit;
    int end = begin * thread_unit + thread_unit - 1; // 最后一个元素
    int min, temp;
    for (int i = start; i <= end; i++)
    {
        min = i;
        for (int j = i; j <= end; j++)
        {
            if (data[min] > data[j]) min = j;
        }
        if (i != min)
        { // 交换
            data[i] = data[i] + data[min];
            data[min] = data[i] - data[min];
            data[i] = data[i] - data[min];
        }
    }
}

void *myprocess(void *arg)
{
    printf("threadid is 0x%lx, working on data %d\n", pthread_self(), *((int *)arg));
    int start = *((int *)arg); // 排序开始的地方
    heapsort(start);
    return NULL;
}

void *merge(void *)
{ // k路归并排序
    int *start = (int *)malloc(10 * sizeof(int));
    int *top = (int *)malloc(10 * sizeof(int));
    int *temp = (int *)malloc(num * sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        start[i] = i * 10;
        top[i] = 10 * (i + 1);
    }
    int count = 0; // temp数组的起始位置
    // 开始归并
    int mark, minimum, flag;
    while (count != num)
    {
        flag = 0;
        for (int i = 0; i < 10; i++)
        {
            if (start[i] < top[i])
            { // 没有超出界限
                if (flag == 0)
                { // 只执行1次
                    minimum = start[i];
                    mark = i; // i标示属于那一段
                }
                flag = 1;
                if (data[minimum] > data[start[i]])
                {
                    minimum = start[i];
                    mark = i;
                }
            }
        }
        start[mark]++;
        temp[count++] = data[minimum];
    }
    for (int i = 0; i < num; i++) data[i] = temp[i];
    free(start);
    free(top);
    free(temp);
    return NULL;
}


int main(int argc, char **argv)
{
    for (int j = 0; j < num; j++)
    {
        data[j] = rand() % 100;
        if (j != 0 && j % thread_unit == 0) std::cout << std::endl;
        std::cout << data[j] << " ";
    }
    std::cout << std::endl;
    pool_init(thread_num); /*线程池中最多3个活动线程*/
    sleep(1);
    /*连续向任务队列中投入10个任务*/
    int *workingnum = (int *)malloc(sizeof(int) * 10);
    int i;
    for (i = 0; i < 10; i++)
    {
        workingnum[i] = i;
        add_task(myprocess, &workingnum[i]);
    }
    sleep(1); // 等待前面10个任务完成
    std::cout << "after sorting:" << std::endl;
    for (int j = 0; j < num; j++)
    {
        if (j != 0 && j % thread_unit == 0) std::cout << std::endl;
        std::cout << data[j] << " ";
    }
    add_task(merge, NULL); // 最后的数据排序
    /*等待所有任务完成*/
    sleep(20);
    /*销毁线程池*/
    pool_destroy();
    std::cout << "after merging:" << std::endl;
    for (int j = 0; j < num; j++)
    {
        if (j != 0 && j % thread_unit == 0) std::cout << std::endl;
        std::cout << data[j] << " ";
    }
    std::cout << std::endl;
    free(workingnum);


    return 0;
}
