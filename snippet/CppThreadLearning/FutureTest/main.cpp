#include <iostream>
#include <future>
#include <thread>

#include "sum.h"


int main()
{
    std::cout << sum<int, int, int>(1, 2, 3) << std::endl;


    return 0;
}
