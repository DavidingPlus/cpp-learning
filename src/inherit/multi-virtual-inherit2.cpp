// multi-virtual-inherit2.cpp
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
    parallelogram(size_t w = 5, size_t h = 3, std::string n = "parallelogram")
        : quadrangle(n), width(w), height(h) {}
    double area() const {
        return double(width * height);
    }
};

class rectangle : virtual public parallelogram {
public:
    rectangle(size_t w = 5, size_t h = 3, std::string n = "rectangle")
        : parallelogram(w, h, n) {}
};

// 多继承会面临很多的问题，这里加上virtual会让祖先对象只有一份
class diamond : virtual public parallelogram {
public:
    diamond(size_t w = 5, size_t h = 3, std::string n = "diamond")
        : parallelogram(w, h, n) {}
    double area() const {
        return parallelogram::area() / 2.0;
    }
};

class square : public rectangle, public diamond {
public:
    square(size_t w = 5, std::string n = "square")
        // 这里直接激活祖先的构造函数
        // 虚继承会略过构造函数，所以如果放rectangle的话不能把参数传递到基类！就会出问题
        : parallelogram(w, w, n) {}

    double area() const {
        return rectangle::area();
    }
};

int main() {
    square s(10);
    std::cout << "area of " << s.whoami() << ": " << s.area() << std::endl;

    return 0;
}
