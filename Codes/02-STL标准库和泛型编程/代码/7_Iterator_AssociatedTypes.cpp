#include <iostream>
using namespace std;

template <class _Type>
struct List_Iterator
{
    typedef std::bidirectional_iterator_tag _iterator_category;
    typedef ptrdiff_t _difference_type;
    typedef _Type _value;
    typedef _Type &_reference;
    typedef _Type *_pointer;
};

int main()
{
    return 0;
}
