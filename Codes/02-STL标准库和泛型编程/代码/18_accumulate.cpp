#include <iostream>
using namespace std;
#include <numeric>

int myfunc(int x, int y)
{
    return x + 2 * y;
}

struct myclass
{
    int operator()(int x, int y) const { return x + 3 * y; }
} myobj;

void test_accumulate()
{
    cout << "test_accumulate().........." << endl;
    int init = 100;
    int nums[] = {10, 20, 30};

    cout << "using default accumulate: ";
    cout << accumulate(nums, nums + 3, init); // 160
    cout << '\n';

    cout << "using functional's minus: ";
    // minus 减法
    cout << accumulate(nums, nums + 3, init, minus<int>()); // 40
    cout << '\n';

    cout << "using custom function: ";
    cout << accumulate(nums, nums + 3, init, myfunc); // 220
    cout << '\n';

    cout << "using custom object: ";
    cout << accumulate(nums, nums + 3, init, myobj); // 280
    cout << '\n';
}

int main()
{
    test_accumulate();

    return 0;
}
