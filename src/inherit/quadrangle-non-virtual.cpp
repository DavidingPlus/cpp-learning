// quadrangle-case.cpp
#include <iostream>
#include <string>
#include <typeinfo>

class quadrangle {
protected:
    std::string name;

public:
    quadrangle(std::string n = "quadrangle") : name(n) {}

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

    // 这里全部输出-1，因为父类不是虚函数，父类指针访问的函数全部找到了父类
    for (auto q : quads)
        std::cout << "area of " << q->whoami() << ": " << q->area() << std::endl;

    std::cout << std::endl
              << typeid(*quads[0]).name() << std::endl
              << typeid(parallelogram).name() << std::endl;

    return 0;
}
