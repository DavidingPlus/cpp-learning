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
    parallelogram(size_t w = 5, size_t h = 3, std::string n = "parallelogram") : name(n), width(w), height(h)  {}
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
