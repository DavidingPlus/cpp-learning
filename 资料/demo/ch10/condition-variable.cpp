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
//condition-variable.cpp

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex m, display;
condition_variable cv;

template <typename ...types>
void print(types ...args) {
    lock_guard<mutex> lock(display);
    (cout << ... << args); 
    cout << endl;
}

void g(int id) {
    unique_lock<mutex> lk(m);
    print("thread ", id, " is waiting...");
    cv.wait(lk);
    print("thread ", id, " terminated");
}

int main() {
    const int n = 6;
    jthread t[n];
    for (int i = 0; i < n; ++i) t[i] = jthread(g, i + 1);
    for (int i = 0; i < n; ++i) t[i].detach();

    print("please press a number to terminate thread(s):",
        "1 for 1, 2 for all, 3 for exit");
    int i;
    while (true) {
        cin >> i; //阻塞主线程
        if (i == 1) cv.notify_one();
        else if (i == 2) cv.notify_all();
        else break;
    }
    print("bye!");
    return 0;
}
