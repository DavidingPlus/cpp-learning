#include <iostream>
using namespace std;
#include <vector>
#include <ext/pool_allocator.h>

template <typename Container>
inline void print(const Container &con)
{
    typedef typename iterator_traits<typename Container::iterator>::value_type Value_Type;
    for (Value_Type val : con)
        cout << val << ' ';
    cout << endl;
}

// 注意语法细节
// Alias Template 没有办法进行特化或者偏特化，如果想要特化或者偏特化需要对写原来的类!!!
template <typename Value_Type>
using Vec = vector<Value_Type, __gnu_cxx::__pool_alloc<Value_Type>>;

int main()
{
    Vec<int> v{1, 2, 3, 4, 5};
    print(v);

    return 0;
}
