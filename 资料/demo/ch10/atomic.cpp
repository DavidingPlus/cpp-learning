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
//atomic.cpp

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;
using namespace chrono;

atomic_int A{0};

void f() {
    for (int i = 0; i <= 10; ++i) {
        cout << "f():" << ++A << endl;
        this_thread::sleep_for(milliseconds(50));
    }
}

void g() {
    for (int i = 0; i <= 10; ++i) {
        this_thread::sleep_for(milliseconds(50));
        cout << "g():" << --A <<  endl;
    }
}

int main() {
    jthread t1(f), t2(g);

    return 0;
}