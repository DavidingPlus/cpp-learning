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
//teacher-case.cpp

#include <iostream>
#include <string>
#include <format>

enum {PROFESSOR = 0, LECTURER, ASSISTANT};
struct pay {
    std::string title;
    double basePay, meritPay;
};
const pay PAY[] = { {"Professor", 6000, 12000}, {"Lecturer", 4500, 7000}, {"Assistant", 3000, 4000} };

class teacher {
protected:
    std::string name;
    pay p;

public:
    teacher(std::string n, pay q) : name(n), p(q) {}
    void information() {
        std::cout << std::format("{} {} : Base pay: {} ; Merit pay: {}\n", p.title, name, p.basePay, p.meritPay);
    }

    void promote(pay q) {
        p = q;
    }
};

class professor : public teacher {
public:
    professor(std::string n) : teacher(n, PAY[PROFESSOR]) {}
};

class lecturer : public teacher {
public:
    lecturer(std::string n) : teacher(n, PAY[LECTURER]) {}
};

class assistant : public teacher {
public:
    assistant(std::string n) : teacher(n, PAY[ASSISTANT]) {}
};

int main() {
    teacher *teachers[] = { new professor("Zhao"), new lecturer("Qian"), new assistant("Sun") };

    for (auto tp : teachers) tp->information();
    teachers[1]->promote(PAY[PROFESSOR]);
    for (auto tp : teachers) tp->information();
    for (auto tp : teachers) delete tp;

    return 0;
}
