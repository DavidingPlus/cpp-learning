#include <iostream>
using namespace std;
#include <bits/stl_tree.h>

// 你传给我啥我给你啥
template <class T>
struct Identity {
    const T &operator()(const T &x) const {
        return x;
    }
    T &operator()(T &x) const {
        return x;
    }
};

int main() {
    typedef int Key_Type;
    typedef int Data_Type;
    typedef int Value_Type;

    _Rb_tree<Key_Type, Value_Type, Identity<Value_Type>, less<Key_Type>, allocator<Value_Type>> rbtree;
    cout << rbtree.size() << endl;   // 0
    cout << sizeof(rbtree) << endl;  // 48 跟插不插元素没关系，因为里面存的是节点指针d
    cout << rbtree.empty() << endl;  // 1

    rbtree._M_insert_unique(3);
    rbtree._M_insert_unique(8);
    rbtree._M_insert_unique(5);
    rbtree._M_insert_unique(9);
    rbtree._M_insert_unique(13);
    rbtree._M_insert_unique(3);       // unique 所以3插不进去
    cout << rbtree.size() << endl;    // 5
    cout << rbtree.empty() << endl;   // 0
    cout << rbtree.count(3) << endl;  // 1

    rbtree._M_insert_equal(3);  // equal 所以3能插进去
    rbtree._M_insert_equal(3);
    cout << rbtree.size() << endl;    // 7
    cout << rbtree.empty() << endl;   // 0
    cout << rbtree.count(3) << endl;  // 3

    return 0;
}
