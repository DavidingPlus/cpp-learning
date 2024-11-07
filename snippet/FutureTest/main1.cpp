#include <iostream>
#include <future>
#include <thread>

#include "sum.h"


int main()
{
    std::future<int> f = std::async(
        std::launch::async,

        sum<int, int, int>,

        1, 10, 100);

    // future::get() 阻塞等待线程结束并获得返回值
    std::cout << f.get() << std::endl;


    return 0;
}
