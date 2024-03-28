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
//mutex.cpp

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace chrono;

const std::string colors[] = {"\033[92m", "\033[33m", "\033[0m"};

mutex m;
void print(int i, int c) {
    // m.lock();
    // cout << i << ' ';
    // m.unlock();
    lock_guard<mutex> lock(m);
    cout << colors[c] << i << colors[2] << ' ';
}

template <int init = 0, int limit = 200>
void f() {
    for (int i = init; i <= limit; i += 2) {
        print(i, init);
        this_thread::sleep_for(milliseconds(10));
    }
}

int main() {
    jthread t1(f<>), t2(f<1>);
    return 0;
}
