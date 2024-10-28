#include <iostream>
#include <random>


int genRandomNumber(int left, int right)
{
    static std::random_device rd;

    static std::mt19937_64 generator(rd());

    std::uniform_int_distribution<int> distribution(left, right);

    return distribution(generator);
}


int main()
{
    for (int i = 0; i < 5; ++i) std::cout << genRandomNumber(1, 100) << ' ' << std::flush;

    std::cout << std::endl;


    return 0;
}
