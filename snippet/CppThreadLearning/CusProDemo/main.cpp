#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <random>


// 链表，临界区数据
struct Node
{

    Node(int val) : m_val(val), m_next(nullptr) {}


    int m_val = 0;

    struct Node *m_next = nullptr;

} *head = nullptr;

// 互斥锁
std::mutex mtx;

// 条件变量
std::condition_variable cond;


// std::random_device 和 std::mt19937_64 改为静态的，全局只有一份。保证语义正确。
int genRandomNumber(int left, int right)
{
    static std::random_device rd;

    static std::mt19937_64 generator(rd());

    std::uniform_int_distribution<int> distribution(left, right);

    return distribution(generator);
}

// 生产者不断头插法向链表中插入结点
void CustomerTask()
{
    while (true)
    {
        // 由于条件变量 std::condition_variable 需要 std::unique_lock<std::mutex>，因此关于加锁解锁的操作全部使用 std::unique_lock<std::mutex>，否则可能段错误，详见 main.cpp.problem
        // std::unique_lock 在构造函数中自动加锁，不用手动加锁。生命周期结束自动解锁，当然也可以手动解锁。
        std::unique_lock<std::mutex> lock(mtx);

        Node *newNode = new Node(genRandomNumber(1, 1000));
        newNode->m_next = head;
        head = newNode;

        std::cout << "add node, val: " << newNode->m_val << ", thread id: " << std::this_thread::get_id() << std::endl;

        lock.unlock();

        // 通过条件变量通知消费者线程，可以解除阻塞
        cond.notify_one();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// 消费者不断从头部释放结点
void ProducerTask()
{
    while (true)
    {
        if (head)
        {
            std::unique_lock<std::mutex> lock(mtx);

            Node *temp = head;

            head = head->m_next;

            std::cout << "delete node, val: " << temp->m_val << ", thread id: " << std::this_thread::get_id() << std::endl;

            delete temp;
            temp = nullptr;

            lock.unlock();

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
        {
            std::unique_lock<std::mutex> lock(mtx);

            // 链表为空，通过条件变量通知生产者线程，自身阻塞
            cond.wait(lock);

            lock.unlock();
        }
    }
}


int main()
{
    // 生产者、消费者各 5 个
    constexpr int threadNum = 5;

    std::thread customers[threadNum], producers[threadNum];

    for (int i = 0; i < threadNum; ++i)
    {
        customers[i] = std::thread(CustomerTask);
        producers[i] = std::thread(ProducerTask);
    }

    for (int i = 0; i < threadNum; ++i)
    {
        customers[i].join();
        producers[i].join();
    }


    return 0;
}
