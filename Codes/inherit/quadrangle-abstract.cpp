// quadrangle-abstract.cpp
#include <iostream>
#include <string>

// 抽象类不能实例化，不能定义对象，但是可以定义指针和引用，因为不需要构造
class quadrangle {
protected:
    std::string name;

public:
    quadrangle(std::string n = "quadrangle") : name(n) {}

    virtual ~quadrangle() {}

public:
    std::string whoami() const {
        return name;
    }

    virtual double area() const = 0;
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
    double area() const {
        return rectangle::area();
    }
};

int main() {
    quadrangle *quads[] = {new parallelogram(), new rectangle(), new diamond(), new square()};

    for (auto q : quads)
        std::cout << "area of " << q->whoami() << ": " << q->area() << std::endl;

    for (auto q : quads)
        delete q;

    return 0;
}
