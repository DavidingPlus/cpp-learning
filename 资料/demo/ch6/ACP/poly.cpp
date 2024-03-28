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
protected:
    string ids;
    size_t edge;

public:
    poly(string _ids = "poly", size_t e = 0) : ids(_ids), edge(e) {}
    ~poly() {}

    string what() const {
        return ids;
    }
};

class quad : public poly {
public:
    quad(string _ids = "quad") : poly(_ids, 4) {}
    ~quad() {}

    double area() const {
        return 0.0;
    }
};

class para : public quad {
protected:
    double width, height;

public:
    para(double w = 1, double h = 1, string _ids = "para") : quad(_ids), width(w), height(h) {}
    ~para() {}

    double area() const {
        return width * height;
    }
};

class rect : public para {
public:
    rect(double w = 1, double h = 1, string _ids = "rect") : para(w, h, _ids) {}
    ~rect() {}
};

class square final : public rect {
public:
    square(double w = 1) : rect(w, w, "square") {}
    ~square() {}
};

int main() {
    quad q;
    square s(8);

    cout << "Derived object assigns to parent object:" << endl;
    q = s;
    cout << q.what() << ' ' << q.area() << endl;

    cout << "Parent reference references derived object:" << endl;
    quad &qr = s;
    cout << qr.what() << ' ' << qr.area() << endl;

    cout << "Parent pointer points to derived object:" << endl;
    quad *qp = &s;
    cout << qp->what() << ' ' << qp->area() << endl;

    return 0;
}