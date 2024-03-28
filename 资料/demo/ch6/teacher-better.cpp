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
//teacher-better.cpp

#include <iostream>
#include <string>
#include <format>

class title {
protected:
    enum {PROFESSOR = 0, LECTURER, ASSISTANT};
    struct pay {
        double basePay, meritPay;
    };
    static pay PAY[3];

    std::string title_name;
    pay p;

public:
    title(std::string tn, size_t index) : title_name(tn), p(PAY[index]) {}
    title(const title &t) : title_name(t.title_name), p(t.p) {}
    title &operator=(const title &t) {
        title_name = t.title_name;
        p = t.p;
        return *this;
    }

    friend class teacher;
};

title::pay title::PAY[3] = { {6000, 12000}, {4500, 7000}, {3000, 4000} };

class professor : public title {
public:
    professor() : title("Professor", title::PROFESSOR) {}
};

class lecturer : public title {
public:
    lecturer() : title("Lecturer", title::LECTURER) {}
};

class assistant : public title {
public:
    assistant() : title("Assistant", title::ASSISTANT) {}
};

class teacher {
protected:
    std::string name;
    title mytitle; //组合

public:
    teacher(std::string n, const title &mt) : name(n), mytitle(mt) {}
    void information() {
        std::cout << std::format("{} {} : Base pay: {} ; Merit pay: {}\n", mytitle.title_name, name, mytitle.p.basePay, mytitle.p.meritPay);
    }

    void promote(const title &t) {
        mytitle = t;
    }
};

const professor TITLE_PROFESSOR;
const lecturer TITLE_LECTURER;
const assistant TITLE_ASSISTANT;

int main() {
    teacher *teachers[] = { new teacher("Zhao", TITLE_PROFESSOR),
                new teacher("Qian", TITLE_LECTURER),
                new teacher("Sun", TITLE_ASSISTANT)
    };

    for (auto tp : teachers) tp->information();
    teachers[1]->promote(TITLE_PROFESSOR);
    for (auto tp : teachers) tp->information();
    for (auto tp : teachers) delete tp;

    return 0;
}
