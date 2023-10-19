#include <assert.h>
using namespace std;
#include <iostream>

// new handler必须return void，然后没有参数
void noMoreMemory() {
    cerr << "out of memory\n";
    abort();
}

void test_set_new_handler() {
    cout << "test_set_new_handler().......... \n";

    set_new_handler(noMoreMemory);

    int* p = new int[100000000000000];  // well, so BIG!
    assert(p);

    p = new int[100000000000000];  //[Warning] integer constant is too large for its type
    assert(p);
}

int main() {
    test_set_new_handler();

    return 0;
}
