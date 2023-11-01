/**
 * @file foo.cpp
 * @author 白忠建 (baizj@uestc.edu.cn)
 * @brief foo类的友元实现
 * @version 0.1
 * @date 2023-11-01
 * 
 * @copyright Copyright (C) 2023 白忠建. All rights reserved.
 * 
 */

#include <format>
#include <cmath>

#include "foo.h"

std::ostream& operator<<(std::ostream& os, foo const& f) {
    return os << std::format("({},{:.1f})", f.i, f.d);
}

bool operator>(foo const& f1, foo const& f2) {
    return (f1.i > f2.i) and (f1.d > f2.d);
}

bool operator==(foo const& f1, foo const& f2) {
    return (f1.i == f2.i) and (fabs(f1.d - f2.d) < 1E-6);
}

foo operator+(foo const& f1, foo const& f2) {
    return foo{f1.i + f2.i, f1.d + f2.d};
}