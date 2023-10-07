// normal-destructor.cpp
#include <iostream>

struct X {
    X() {
        std::cout << "X()" << std::endl;
    }

    // 父类的析构函数可以是虚的，并且应该是虚的，这样才能如果用父类指针指向的时候，能够从子类开始往父类进行析构，这也符合我们的预期
    // 析构函数不能被继承，构造函数可以被继承
    virtual ~X() {
        std::cout << "~X()" << std::endl;
    }
};

struct Y : public X {
    Y() {
        std::cout << "Y()" << std::endl;
    }

    ~Y() {
        std::cout << "~Y()" << std::endl;
    }
};

int main() {
    X *p = new Y;
    delete p;

    return 0;
}
