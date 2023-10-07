// quadrangle-case.cpp
#include <iostream>
#include <string>

class quadrangle {
private:
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

class parallelogram {
private:
    std::string name;
    size_t width, height;

public:
    parallelogram(size_t w = 5, size_t h = 3, std::string n = "parallelogram") : name(n), width(w), height(h) {}
    std::string whoami() const {
        return name;
    }
    double area() const {
        return double(width * height);
    }
};

class rectangle {
private:
    std::string name;
    size_t width, height;

public:
    rectangle(size_t w = 5, size_t h = 3, std::string n = "rectangle") : name(n), width(w), height(h) {}
    std::string whoami() const {
        return name;
    }
    double area() const {
        return double(width * height);
    }
};

int main() {
    parallelogram para(7);
    rectangle rect(20, 12);

    std::cout << "area of " << para.whoami() << ": " << para.area() << std::endl;
    std::cout << "area of " << rect.whoami() << ": " << rect.area() << std::endl;

    return 0;
}
