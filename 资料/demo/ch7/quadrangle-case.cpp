/*
 * Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
 * 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */


//bzj^_^
//quadrangle-case.cpp

#include <iostream>
#include <string>
#include <typeinfo>

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
    parallelogram(size_t w = 5, size_t h = 3, std::string n = "parallelogram") : quadrangle(n), width(w), height(h)  {}
    double area() const {
        return double(width * height);
    }
};

class rectangle : virtual public parallelogram {
public:
    rectangle(size_t w = 5, size_t h = 3, std::string n = "rectangle") : parallelogram(w, h, n) {}
};

class diamond : virtual public parallelogram {
public:
    diamond(size_t w = 5, size_t h = 3, std::string n = "diamond") : parallelogram(w, h, n) {}
    double area() const {
        return parallelogram::area() / 2.0;
    }
};

class square: public rectangle, public diamond {
public:
    square(size_t w = 5, std::string n = "square") : parallelogram(w, w, n) {}
    double area() const {
        return rectangle::area();
    }
};

int main() {
    parallelogram p;
    rectangle r;
    diamond d;
    square s;
    quadrangle *quads[] = { &p, &r, &d, &s };

    for (auto q : quads) std::cout << "area of " << q->whoami() << ": " << q->area() << std::endl;

    std::cout << typeid(*quads[0]).name() << ',' << typeid(parallelogram).name();

    return 0;
}
