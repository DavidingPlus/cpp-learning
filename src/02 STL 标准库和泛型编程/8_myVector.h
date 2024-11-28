#ifndef __MYVECTOR__
#define __MYVECTOR__

#include <ext/pool_allocator.h>
template <class T, class Alloc = __gnu_cxx::__pool_alloc<T>>
// 这是数据的定义，后面的插入这些太复杂了，不写
class myvector
{
    // 重命名一些东西
public:
    typedef T value_type;
    typedef value_type *iterator;
    typedef value_type &reference;
    typedef size_t size_type;

protected:
    iterator start;
    iterator finish;
    iterator end_of_storage;

private:
    iterator begin() const { return start; }
    iterator end() const { return finish; }
    size_type size() const { return size_type(end() - begin()); }
    size_type capacity() const { return size_type(end_of_storage - begin()); }
    bool empty() const { return begin() == end(); }
    reference operator[](size_type n) { return *(begin() + n); }
    reference front() { return *begin(); }
    reference back() { return *(end() - 1); }
};

#endif
