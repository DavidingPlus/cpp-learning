/**
 * @file foo.h
 * @author 白忠建 (baizj@uestc.edu.cn)
 * @brief 用于测试的类
 * @version 0.1
 * @date 2023-11-01
 * 
 * @copyright Copyright (C) 2023 白忠建. All rights reserved.
 * 
 */

#pragma once

struct foo {
    int i;
    double d;

    foo(int _i = 0, double _d = 0) : i(_i), d(_d) {}

    friend std::ostream& operator<<(std::ostream& os, foo const& f);
    friend bool operator>(foo const& f1, foo const& f2);
    friend bool operator==(foo const& f1, foo const& f2);
    friend foo operator+(foo const& f1, foo const& f2);
};