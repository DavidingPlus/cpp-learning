#include <iostream>
using namespace std;
#include "25_MyStrNoMove.h"
#include "25_Mystring.h"
#include "25_test.h"

int main() {
    long value = 3 * 10e5;

    Test::test_vector(value);
    Test::clear();

    Test::test_list(value);
    Test::clear();

    Test::test_deque(value);
    Test::clear();

    Test::test_multiset(value);
    Test::clear();

    // Test::test_unordered_multiset(value);
    // Test::clear();

    return 0;
}
