#include <iostream>
using namespace std;

int main() {
    []() -> void {
        cout << "hello lambda" << endl;
    }();  // 前三个是格式 最后一个括号代表调用

    auto I = []() -> void {
        cout << "hello lambda" << endl;
    };
    I();

    int id1 = 0, id2 = 0;
    // 为什么下面打印出来是0 1 2
    // 因为这里的id1传进去是0，还没走到下面
    // 由于是 value 传递，所以是copy操作，内部的id不会影响外面的id
    auto f = [id1, &id2]() mutable {
        // 如果不写 mutable ，这个id进来之后只能read only，不能++
        cout << "id1: " << id1 << ',' << "id2: " << id2 << endl;
        ++id1;
        ++id2;
    };

    // 上面lambda表达式的相对接近的写法(不对等，有小区别)
    // class Functor {
    // private:
    //     int id1;  // copy of outside id1
    //     int id2;  // reference of outside id2

    // public:
    //     void operator()() {
    //         cout << "id1: " << id1 << ',' << "id2: " << id2 << endl;
    //         ++id1;
    //         ++id2;
    //     }
    // };
    // Functor f;

    id1 = 42, id2 = 42;
    f();  // 0 42
    f();  // 1 43
    f();  // 2 44
    cout << id1 << ' ' << id2 << endl;

    return 0;
}
