// multi-inherit-error.cpp
#include <iostream>
#include <string>

class quadrangle {
protected:
    std::string name;

public:
    quadrangle(std::string n = "quadrangle") : name(n) {}
    std::string whoami() const {
        return name;
    }
    double area() const {
        return -1.0;
    }
};

class parallelogram : public quadrangle {
protected:
    size_t width, height;

public:
    parallelogram(size_t w = 5, size_t h = 3, std::string n = "parallelogram") : quadrangle(n), width(w), height(h) {}
    double area() const {
        return double(width * height);
    }
};

class rectangle : public parallelogram {
public:
    rectangle(size_t w = 5, size_t h = 3, std::string n = "rectangle") : parallelogram(w, h, n) {}
};

class diamond : public parallelogram {
public:
    diamond(size_t w = 5, size_t h = 3, std::string n = "diamond") : parallelogram(w, h, n) {}
    double area() const {
        return parallelogram::area() / 2.0;
    }
};

// 这两个父类都来自于parallelogram的父类，那么我访问的时候是访问哪一个呢？这就是二义性！
// 解决方法：在父类的继承祖先的时候加上virtual表示虚继承，这样内存中就只会出现一个祖先对象
class square : public rectangle, public diamond {
public:
    square(size_t w = 5, std::string n = "square") : rectangle(w, w, n), diamond(w, w, n) {}
};

int main() {
    square s(10);
    std::cout << "area of " << s.whoami() << ": " << s.area() << std::endl;

    return 0;
}
