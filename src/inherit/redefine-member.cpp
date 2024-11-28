// redefine-member.cpp
#include <iostream>
#include <string>
using std::string;

class base {
protected:
    string name;

public:
    base() {
        name = "base";
    }

    void whoami() {
        std::cout << name << std::endl;
    }
};

class derived : public base {
protected:
    string name;  // 重定义成员。这个成员与基类的同名成员不同。因此，在derived内部，有两个name成员。

public:
    derived() : base() {
        name = "derived";  // 初始化派生类自己的
    }

    string get_name() const {
        return name;  // 获取派生类自己的
    }
};

class derived2 : public base {
public:
    derived2() : base() {
        name = "derived";  // 初始化基类的，也就是派生类继承的
    }

    string get_name() const {
        return name;  // 获取基类的，也就是派生类继承的
    }
};

// 也许是最佳方案
class base2 {
protected:
    string name;

public:
    base2(string n = "base") : name(n) {}

    void whoami() {
        std::cout << name << std::endl;
    }
};

class derived3 : public base2 {
public:
    derived3(string n = "derived") : base2(n) {}  // 激活基类的构造函数来完成初始化

    string get_name() const {
        return name;
    }
};

int main() {
    derived d;
    d.whoami();
    std::cout << d.get_name() << std::endl;

    // derived2 d2;
    // d2.whoami();
    // std::cout << d2.get_name() << std::endl;

    // derived2 d3;
    // d3.whoami();
    // std::cout << d3.get_name() << std::endl;

    return 0;
}
