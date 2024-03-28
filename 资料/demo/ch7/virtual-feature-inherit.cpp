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
//virtual-feature-inherit.cpp

#include <iostream>
#include <string>

class quadrangle {
public:
    virtual std::string whoami() const {
        return "quadrangle";
    }
};

class parallelogram : public quadrangle {
public:
    std::string whoami(std::string prefix) const {
        return prefix + "parallelogram";
    }
};

class rectangle : public parallelogram {
public:
    std::string whoami() const {
        return "rectangle";
    }
};

int main() {
    parallelogram p;

    quadrangle &rp = p;
    std::cout << rp.whoami() << std::endl;
    //std::cout << rp.whoami("I'm ") << std::endl; //error
    std::cout << p.whoami("I'm ") << std::endl;

    rectangle r;
    quadrangle &rr = r;
    std::cout << rr.whoami() << std::endl;

    return 0;
}
