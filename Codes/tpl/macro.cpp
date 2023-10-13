// macro.cpp
// 宏并不是一个好的选择，因为没有一些检测机制，可能会不安全
// 用 g++ -E 可以进行宏展开，就是把宏展开之后的真正的代码

#define pi(type) ((type)(3.1415926536))

#define lt(a, b) ((a) < (b))

#define llist(type)            \
    class linked_list_##type { \
    public:                    \
        using value_t = type;  \
    };

llist(int) llist(double)

    // 主程序段
    int main() {
    bool b = lt(1, 2);
    int area = 2 * 2 * pi(int);
    linked_list_int l1;
    linked_list_double l2;

    return 0;
}
