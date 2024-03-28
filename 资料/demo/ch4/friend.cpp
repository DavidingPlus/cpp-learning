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
//friend.cpp

#include <iostream>

class X {
private:
    int i = 1;

public:
    int& get() { return i; }

    friend int set(X&, int);
    friend class Y;
};

int set(X& o, int j) { return o.i = j; }

struct Y {
    int set(X& o, int j) { return o.i = j; }
};

int main() {
    X x;

    set(x, 2);
    std::cout << x.get();

    Y y;
    y.set(x, 3);
    std::cout << ' ' << x.get();

    return 0;
}
