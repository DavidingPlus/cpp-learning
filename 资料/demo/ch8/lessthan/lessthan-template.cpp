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
//lessthan-template.cpp

#include <iostream>
import <cstring>

using cstring = char *;

class square
{
private:
    size_t width;
public:
    square(size_t w = 5) : width(w) {}
    operator size_t () const { return width; }
};

template <typename T>
bool lt(T a, T b) { return a < b; }

template <>
bool lt(cstring a, cstring b) { return strcmp(a, b) < 0; }

template <typename T = int, T threshold = 10>
bool lt2(T a) { return a < threshold; }

auto lt3 = [](auto a, auto b)->bool { return a < b; };

int main()
{
    int a{1}, b{2};
    double c{4.0}, d{-1.0};
    square e{6}, f{9};
    cstring g{const_cast<cstring>("abc")}, h{const_cast<cstring>("ABC")};
    auto bool2literal = [](bool b) { std::cout << (b ? "true" : "false") << std::endl; };

    bool2literal(lt(a, b));
    bool2literal(lt(c, d));
    bool2literal(lt(e, f)); //operator size_t()起作用
    bool2literal(lt(g, h));
    bool2literal(lt2<int,10>(a));
    bool2literal(lt2(a));
    bool2literal(lt2<int>(b));
    bool2literal(lt2<int, 0>(b));
    bool2literal(lt3(a, b));

    return 0;
}
