/* 
 * Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
 * 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2. 
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2 
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details. 
 */


#include <iostream>
using namespace std;

class poly {
private:
    string ids;
    size_t edge;

public:
    poly(string _ids = "poly") : ids(_ids), edge(0) {}
    ~poly() {}

    string what() const { return ids; }
};

class quad {
private:
    string ids;
    size_t edge;

public:
    quad(string _ids = "quad") : ids(_ids), edge(4) {}
    ~quad() {}

    string what() const { return ids; }
    double area() const { return 0.0; }
};

class para {
private:
    string ids;
    size_t edge;
    double width, height;

public:
    para(double w = 1, double h = 1, string _ids = "para") : ids(_ids), edge(4), width(w), height(h) {}
    ~para() {}

    string what() const { return ids; }
    double area() const { return width * height; }
};

class rect {
private:
    string ids;
    size_t edge;
    double width, height;

public:
    rect(double w = 1, double h = 1, string _ids = "rect") : ids(_ids), edge(4), width(w), height(h) {}
    ~rect() {}

    string what() const { return ids; }
    double area() const { return width * height; }
};

int main() {
    para p(7, 4);
    cout << p.what() << ' ' << p.area() << endl;

    rect r(10, 5);
    cout << r.what() << ' ' << r.area() << endl;
    
    return 0;
}