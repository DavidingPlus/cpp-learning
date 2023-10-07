#include <iostream>
using namespace std;

namespace my1
{
    static void test()
    {
        cout << "I am in namespace my1" << endl;
    }
}

namespace my2
{
    static void test()
    {
        cout << "I am in namespace my2" << endl;
    }
}

int main()
{
    my1::test();
    my2::test();

    return 0;
}
