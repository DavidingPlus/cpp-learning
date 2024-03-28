#include <iostream>
#include <ctime>
#include <fstream>
#define MAXSIZE 1000

int main()
{
    srand(time(NULL)); // 先种种子

    // 打开写的文件流
    std::ofstream ofs;
    ofs.open("/mnt/d/Code/Code-C++/操作系统实验/2.txt", std::ios::out);

    for (int i = 0; i < MAXSIZE; ++i)
    {
        int num = rand() % 9 + 1; // 生成一个1-9之间的随机数
        ofs << num << std::endl;
        std::cout << num << std::endl;
    }

    ofs.close();

    return 0;
}