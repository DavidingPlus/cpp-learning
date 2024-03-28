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
//packaged-task.cpp

#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std;
using namespace chrono;

struct data_t {
    int i;
    char ch;
};

data_t task(int i, char ch) {
    this_thread::sleep_for(milliseconds(1500));
    return {i, ch};
}

using task_t = data_t (int, char);

int main() {
    packaged_task<task_t> tsk(task);
    auto result_f = tsk.get_future();

    auto start = steady_clock::now();
    thread t(move(tsk), 4, 'D'); //call of move() is very important!
    t.detach();

    auto result = result_f.get();
    auto end = steady_clock::now();
    cout << "wait for " << duration_cast<milliseconds>(end - start).count() << "ms" << endl;
    cout << "the result is: " << result.i << ',' << result.ch << endl;

    return 0;
}