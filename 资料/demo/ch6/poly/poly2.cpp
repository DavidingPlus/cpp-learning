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

struct poly {
    string ids;
    size_t edge;

    poly(string _ids = "poly") : ids(_ids), edge(0) {}
    ~poly() {}

    string what() const { return ids; }
};

struct quad {
    poly p;

    quad(string _ids = "quad") {
        p.ids = _ids;
        p.edge = 4;
    }
    ~quad() {}

    string what() const { return p.what(); }
    double area() const { return 0.0; }
};

struct para {
    quad q;
    double width, height;

    para(double w = 1, double h = 1, string _ids = "para") : width(w), height(h) {
        q.p.ids = _ids;
        q.p.edge = 4;
    }
    ~para() {}

    string what() const { return q.what(); }
    double area() const { return width * height; }
};

struct rect {
    para p;

    rect(double w = 1, double h = 1, string _ids = "rect") {
        p.q.p.ids = _ids;
        p.q.p.edge = 4;
        p.width = w;
        p.height = h;
    }
    ~rect() {}

    string what() const { return p.what(); }
    double area() const { return p.area(); }
};

int main() {
    para p(7, 4);
    cout << p.what() << ' ' << p.area() << endl;

    rect r(10, 5);
    cout << r.what() << ' ' << r.area() << endl;

    return 0;
}