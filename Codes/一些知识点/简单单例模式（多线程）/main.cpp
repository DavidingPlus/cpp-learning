#include <iostream>
#include <thread>
#include <unistd.h>

#include "singleton.h"

void run()
{
    sleep(1);

    // 我让s2放在子线程中跑，看得出的结果如何
    // res: 结果相同，意思是在程序中单例对象只有一份，被所有线程共享；但是在单例中写线程相关的接口系统会根据不同线程作不同的处理，因此这里的单例是没毛病的，例如这里的 threadID()
    Singleton *s2 = Singleton::getInstance();
    s2->print();
    std::cout << "child threadID: " << s2->threadID() << '\n';
}

int main()
{
    // Singleton s;  // error

    Singleton *s1 = Singleton::getInstance();
    s1->print();
    std::cout << "main threadID: " << s1->threadID() << '\n';

    std::thread t(run);

    t.join();

    s1->releaseInstance();

    return 0;
}
