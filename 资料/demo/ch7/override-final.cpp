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
//override-final.cpp

struct X {
    virtual void f() {}
    virtual void g() {}
};

struct Y : public X {
    void f() final {} //OK，这是最终版本，派生类不能覆盖
    void g() override {} //OK，显式覆盖
};

struct Z final : public Y { //Z是最终派生类，它不能再有子代了
    void f() override {} //error
    void g() override {} //OK
};

struct W : public Z {}; //error

int main() {
    return 0;
}