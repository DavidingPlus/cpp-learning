// quadrangle-virtual.cpp
#include <iostream>
#include <string>

class quadrangle {
protected:
    std::string name;

public:
    quadrangle(std::string n = "quadrangle") : name(n) {}

public:
    std::string whoami() const {
        return name;
    }

    // 最早的父类变为虚函数，子类可以对这个成员进行覆写，父类指针访问这个接口会得到子类对应的实现，这个就是多态
    virtual double area() const {
        return -1.0;
    }
};

class parallelogram : public quadrangle {
protected:
    size_t width, height;

public:
    parallelogram(size_t w = 5, size_t h = 3, std::string n = "parallelogram")
        : quadrangle(n), width(w), height(h) {}

public:
    double area() const {
        return double(width * height);
    }
};

class rectangle : virtual public parallelogram {
public:
    rectangle(size_t w = 5, size_t h = 3, std::string n = "rectangle")
        : parallelogram(w, h, n) {}
};

class diamond : virtual public parallelogram {
public:
    diamond(size_t w = 5, size_t h = 3, std::string n = "diamond")
        : parallelogram(w, h, n) {}

public:
    double area() const {
        return parallelogram::area() / 2.0;
    }
};

class square : public rectangle, public diamond {
public:
    square(size_t w = 5, std::string n = "square") : parallelogram(w, w, n) {}

public:
    double area() const {
        return rectangle::area();
    }
};

int main() {
    parallelogram p;
    rectangle r;
    diamond d;
    square s;
    quadrangle *quads[] = {&p, &r, &d, &s};

    for (auto q : quads)
        std::cout << "area of " << q->whoami() << ": " << q->area() << std::endl;

    return 0;
}
