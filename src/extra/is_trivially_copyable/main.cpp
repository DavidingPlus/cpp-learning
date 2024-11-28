#include <iostream>
#include <type_traits>

struct DataT1
{
    int x;
    std::string str;
};

struct DataT2
{
    int x;
    DataT1 t;
};

struct DataT3
{
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
};

class DataT4
{

public:
    DataT4() { p = new int(0); }

    ~DataT4()
    {
        if (p)
        {
            delete p;
            p = nullptr;
        }
    }

    int *p = nullptr;
};

int main()
{
    std::cout << std::is_trivially_copyable<DataT1>::value << '\n';
    std::cout << std::is_trivially_copyable<DataT2>::value << '\n';
    std::cout << std::is_trivially_copyable<DataT3>::value << '\n';
    std::cout << std::is_trivially_copyable<DataT4>::value << '\n';

    return 0;
}
