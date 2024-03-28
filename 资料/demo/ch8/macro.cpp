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
//macro.cpp

#define pi(type) ((type)(3.1415926536))
#define lt(a, b)  ((a) < (b))
#define llist(type) class linked_list_##type \
                    {   \
                    public: \
                        using value_t = type;  \
                    };

llist(int)
llist(double)

int main() { 
    bool b = lt(1, 2);
    int area = 2 * 2 * pi(int);
    linked_list_int l1;
    linked_list_double l2;

    return 0; 
}
