// quadrangle-case-composition.cpp
#include <iostream>
#include <string>

struct quadrangle {
    std::string name;

    quadrangle(std::string n = "quadrangle") : name(n) {}
    std::string whoami() const {
        return name;
    }
    double area() const {
        return -1.0;
    }
};

struct parallelogram {
    quadrangle quad;
    size_t width, height;

    parallelogram(size_t w = 5, size_t h = 3, std::string n = "parallelogram") : width(w), height(h) {
        quad.name = n;
    }
    std::string whoami() const {
        return quad.whoami();
    }
    double area() const {
        return double(width * height);
    }
};

struct rectangle {
    parallelogram para;

    rectangle(size_t w = 5, size_t h = 3, std::string n = "rectangle") {
        para.width = w;
        para.height = h;
        para.quad.name = n;
    }
    std::string whoami() const {
        return para.whoami();
    }
    double area() const {
        return para.area();
    }
};

int main() {
    parallelogram para(7);
    rectangle rect(20, 12);

    std::cout << "area of " << para.whoami() << ": " << para.area() << std::endl;
    std::cout << "area of " << rect.whoami() << ": " << rect.area() << std::endl;

    return 0;
}
