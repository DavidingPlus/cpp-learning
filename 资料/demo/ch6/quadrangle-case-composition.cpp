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
//quadrangle-case-composition.cpp

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
