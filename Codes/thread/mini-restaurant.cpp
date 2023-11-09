/*
 * Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
 * 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http:// license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */

/**
 * @file mini-restaurant.cpp
 * @author 白忠建 (baizj@uestc.edu.cn)
 * @brief 生产者-消费者模型：演示多线程的互斥与共享
 * @version 0.1
 * @date 2023-11-09
 *
 * @copyright Copyright (C) 2023 白忠建. All rights reserved.
 *
 */

#include <atomic>
#include <condition_variable>
#include <cstdio>
#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <thread>
using namespace std;
using namespace chrono;

// ---------------------------------------------------------------------------
// 因为输出信息较多，所以通过颜色来区分
const string grey{"\033[90m"}, green{"\033[92m"}, amber{"\033[33m"},
    magenta{"\033[95m"}, turquoise{"\033[96m"}, ende{"\033[0m"};

// ---------------------------------------------------------------------------
// 用于标准输出流的排他锁
mutex pnt_m;

/**
 * @brief 打印多个任意类型的数据并换行
 *
 * @tparam types 变长类型参数包
 * @param args 变长参数包
 */
template <typename... types>
void println(types&&... args) {
    lock_guard<mutex> lock(pnt_m);

    (cout << ... << args);
    cout << endl;
}

// ---------------------------------------------------------------------------
// 订单项
struct course_t {
    size_t table;   // 桌号
    string course;  // 菜品
};

using order_t = list<course_t>;

// 订单。这是一个被竞争的数据
order_t order{
    {1, "fish"},
    {4, "fish"},
    {1, "brocoli"},
    {1, "mushroom"},
    {1, "vegi soup"},
    {2, "vegi soup"},
    {2, "mutton"},
    {3, "beef"},
    {4, "beef"},
    {3, "chicken"},
    {3, "spaghetti"},
    {2, "mushroom"}};

// 订单数
int const total = order.size();
int const _total = -total;

// ---------------------------------------------------------------------------
// 已做好的菜品列表
order_t cooked;

// ---------------------------------------------------------------------------
// 互斥量，分别用于订单锁、做好的菜品锁、铃
mutex order_m, cooked_m, bell_m;

// 信号量
condition_variable bell;  // 菜品做好后主厨按的铃

// 原子量：主厨做好的菜品数（正），服务员上菜的数量（负）
atomic_int volatile count_cooked{0}, count_served{0};

// ---------------------------------------------------------------------------
class restaurant_staff;  // 餐厅员工类的超前声明

/**
 * @brief 厨房工作的接口
 *
 */
struct restaurant_job {
    restaurant_job() = default;                              // 默认构造函数
    restaurant_job(restaurant_job const&) = delete;          // 禁止复制
    virtual void do_job(restaurant_staff const&) const = 0;  // 工作线程接口
};

// ---------------------------------------------------------------------------
/**
 * @brief 餐厅员工类。最终类。应用组合聚集优先原则。因为重载了()，所以是个functor
 *
 */
class restaurant_staff final {
private:
    string const name;          // 姓名
    restaurant_job const& job;  // 承担的厨房工作
    string const color;         // 显示颜色

public:
    restaurant_staff(string const& n, restaurant_job const& j, string const& c) : name(n), job(j), color(c) {}

    /**
     * @brief 重载的()运算符，用于启动对应的厨房工作
     *
     */
    void operator()() {
        job.do_job(*this);  // 多态
    }

    // 友元声明
    friend class chef;    // 主厨类
    friend class server;  // 服务员类
};

// ---------------------------------------------------------------------------
/**
 * @brief 厨房工作之主厨。最终子类
 *
 */
struct chef final : public restaurant_job {
    using restaurant_job::restaurant_job;  // 构造函数继承

    /**
     * @brief 接口实现。工作流程：1. 从order获取一项；2. 做菜；3. 将做好的菜品加入cooked；4. 按铃通知服务员
     *
     * @param who 厨房员工
     */
    void do_job(restaurant_staff const& who) const override {
        // TODO

        // Linux和Powershell终端都支持彩色显式
        // println(who.color, ++count_cooked, ": Chef ", who.name, " is cooking '", c, "' for table ", t, ende);
        // this_thread::sleep_for(milliseconds(100)); // 睡眠一段时间，模拟做菜的耗时
        // println(grey, "\tCourse '", c, "' for table ", t, " is done", ende);
    }
};

/**
 * @brief 厨房工作之服务员。最终子类
 *
 */
struct server final : public restaurant_job {
    using restaurant_job::restaurant_job;

    /**
     * @brief 接口实现。工作流程：1. 等待铃响；2. 从cooked获取一项；3. 上菜
     *
     * @param who 厨房员工
     */
    void do_job(restaurant_staff const& who) const override {
        // TODO
        count_served = _total;  // 编码补全后请删除这行

        // println(who.color, --count_served, ": Server ", who.name, " is dishing up '", c, "' for table ", t, ende);
        // this_thread::sleep_for(milliseconds(80)); // 睡眠，模拟上菜耗时
    }
};

// 两种厨房工作是常量
const chef Cf;
const server Sv;

int main() {
    println("Restaurant open: ", total, " courses\n");

    // 定义4位厨房员工
    restaurant_staff z("Zhang", Cf, green), l("Li", Cf, amber), w("Wang", Sv, magenta), x("Xiao", Sv, turquoise);
    // 创建并启动线程。线程模板是functor
    jthread srv1(w), srv2(x), chef1(z), chef2(l);

    // 模拟阻塞主线程
    while (count_served != _total)
        ;

    println("\nRestaurant close");

    return 0;
}
