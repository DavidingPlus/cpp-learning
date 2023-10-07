// quadrangle-inherit.cpp
#include <iostream>
#include <string>

class quadrangle {
    // protected段：为了让子类能够正确访问父类的私有段，这里引入protected段
protected:
    std::string name;

public:
    quadrangle(std::string n = "quadrangle") : name(n) {}

    ~quadrangle() {}

public:
    std::string whoami() const {
        return name;
    }

    double area() const {
        return -1.0;
    }
};

class parallelogram : public quadrangle {
protected:
    size_t width, height;  // 子类会继承父类的所有特性，因此这里就有name成员了，没有必要再写了

public:
    parallelogram(size_t w = 5, size_t h = 3, std::string n = "parallelogram")
        // 使用初始化序列的成员必须是本类的直接成员，从父类继承而来的成员不允许直接初始化，而最好调用父类的API进行初始化，比如构造函数
        : quadrangle(n), width(w), height(h) {}

    ~parallelogram() {}

public:
    double area() const {
        return double(width * height);
    }
};

class rectangle : public parallelogram {
public:
    rectangle(size_t w = 5, size_t h = 3, std::string n = "rectangle") : parallelogram(w, h, n) {}

    ~rectangle() {}
};

int main() {
    parallelogram para(7);
    rectangle rect(20, 12);

    std::cout << "area of " << para.whoami() << ": " << para.area() << std::endl;
    std::cout << "area of " << rect.whoami() << ": " << rect.area() << std::endl;

    return 0;
}
