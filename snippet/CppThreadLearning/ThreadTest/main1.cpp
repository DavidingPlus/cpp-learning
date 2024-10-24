#include <iostream>
#include <thread>


void doIt() { std::cout << "Hello, " << std::flush; }


int main()
{
    // 线程是在 thread 对象被定义的时候开始执行的。而不是在调用 join() 时才执行的，调用 join() 只是阻塞等待线程结束并回收资源。
    std::thread
        a(doIt),
        b([]()
          { std::cout << "World!" << std::endl; });

    // 没有执行 join() 或 detach() 的线程在程序结束时会引发异常。
    a.join();
    b.join();


    return 0;
}
