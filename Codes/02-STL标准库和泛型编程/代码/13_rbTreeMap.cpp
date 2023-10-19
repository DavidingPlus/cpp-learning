#include <iostream>
using namespace std;
#include <bits/stl_tree.h>

// 源代码这么写的，我没看懂
template <class Pair>
struct SelectFirst
{
    template <class Pair2>
    typename Pair2::First_type &
    operator()(Pair2 &x) const
    {
        return x.first;
    }

    // typedef typename Pair::first_type First_Type;
    // inline First_Type &
    // operator()(Pair &x) const
    // {
    //     return x.first;
    // }
};

// c++11之前是这样写的，但是在这里就会报错
template <class Pair>
struct _SelectFirst : public unary_function<Pair, typename Pair::First_type>
{
    typename Pair::First_Type &
    opeartor()(Pair &x) const
    {
        return x.first;
    }
};

int main()
{
    typedef int Key_Type;
    typedef char Data_Type;
    typedef pair<const Key_Type, Data_Type> Value_Type;

    // _Rb_tree<Key_Type, Value_Type, _Select1st<Value_Type>, less<int>> rbtree;
    _Rb_tree<Key_Type, Value_Type, SelectFirst<Value_Type>, less<Key_Type>> rbtree; // error
    // select1st怎么写不知道
    cout << rbtree.size() << endl;  // 0
    cout << sizeof(rbtree) << endl; // 48 跟插不插元素没关系，因为里面存的是节点指针d
    cout << rbtree.empty() << endl; // 1

    rbtree._M_insert_unique(make_pair(3, 'a'));
    rbtree._M_insert_unique(make_pair(8, 'b'));
    rbtree._M_insert_unique(make_pair(5, 'c'));
    rbtree._M_insert_unique(make_pair(9, 'd'));
    rbtree._M_insert_unique(make_pair(13, 'e'));
    rbtree._M_insert_unique(make_pair(3, 'f')); // unique 所以3插不进去
    cout << rbtree.size() << endl;              // 5
    cout << rbtree.empty() << endl;             // 0
    cout << rbtree.count(3) << endl;            // 1

    rbtree._M_insert_equal(make_pair(3, 'a')); // equal 所以3能插进去
    rbtree._M_insert_equal(make_pair(3, 'a'));
    cout << rbtree.size() << endl;   // 7
    cout << rbtree.empty() << endl;  // 0
    cout << rbtree.count(3) << endl; // 3

    return 0;
}
