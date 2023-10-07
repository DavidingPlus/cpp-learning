#include <iostream>
using namespace std;
#define SIZE 1e6
#include <string>
#include <vector>
#include <list>
#include <deque>

template <typename Type>
inline void output_static_data(const Type &obj)
{
    cout << "static_data: " << endl; // 输出静态成员
}

// template template paremeter 双重模板参数
template <class Value_Type,
          template <class> // 这样写表示 Container模板使用 Value_Type 类型
          class Container>
// 这里由于传入的是容器，绝大多数的容器都有两个参数，第一个是元素类型，第二个是分配器，然而分配器又是以元素类型的模板
// 编译器无法推导第二个分配器的参数，虽然有默认值，所以就需要用到 Alias 来设置
class XCls
{
private:
    Container<Value_Type> c;

public:
    XCls()
    {
        for (long i = 0; i < SIZE; ++i)
            c.insert(c.end(), Value_Type());

        output_static_data(Value_Type());
        Container<Value_Type> c1(c);
        Container<Value_Type> c2(std::move(c));
        c1.swap(c2);
    }
};

#include <ext/pool_allocator.h>
namespace Alias
{
    template <typename Value_Type>
    using Vec = vector<Value_Type, __gnu_cxx::__pool_alloc<Value_Type>>;

    template <typename Value_Type>
    using Lst = list<Value_Type, __gnu_cxx::__pool_alloc<Value_Type>>;

    template <typename Value_Type>
    using Deq = deque<Value_Type, __gnu_cxx::__pool_alloc<Value_Type>>;
}

using namespace Alias;
int main()
{
    XCls<string, Vec> c;
    XCls<string, Lst> c2;
    XCls<string, Deq> c3;

    return 0;
}
