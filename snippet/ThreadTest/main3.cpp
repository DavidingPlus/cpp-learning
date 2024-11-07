#include <iostream>
#include <thread>


template <class T>
void changevalue(T &x, T val) { x = val; }


int main()
{
    constexpr int threadNum = 100;

    std::thread th[threadNum];

    int nums[threadNum];

    // 回调函数的参数是一个左值引用，但是 std::thread 需要的是右值引用，因此直接传入编译器会报错
    // std::ref 可以包装按引用传递的值；std::cref 可以包装按常量引用传递的值。这样就能把左值引用包装成右值引用
    for (int i = 0; i < threadNum; i++) th[i] = std::thread(changevalue<int>, std::ref(nums[i]), i + 1);

    for (int i = 0; i < threadNum; i++)
    {
        th[i].join();

        std::cout << nums[i] << ' ';
    }

    std::cout << std::endl;


    return 0;
}
