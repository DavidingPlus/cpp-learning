/*
 * Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
 * 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */


struct X {
    int a, b;
} g{0, 1}; //x.a = 0, x.b = 1

X f(X o) {
    return {1 + o.a, 2 + o.b};
}

int main() {
    int a = {1}; //等价于 int a = 1
    int b{2}; //等价于 int b = 2
    a = b; b = a; //无用，但可避免编译警告

    int *p = new int[4] {1, 2, 3, 4}; //数组p的每个元素都被初始化
    delete[] p;

    auto e = f({3, 4}); //e的类型是X，其值是{4, 6}
    e = e; //无用，但可避免编译警告
    X n; //n未初始化
    n = { 7, 8 }; //赋值

    class Y {
    public:
        int c; double d;
        Y(int x, double y) : c(x), d(y) {}
    } m{5, 6.0}; //m.c = 5，m.d = 6.0

    return 0;
}
