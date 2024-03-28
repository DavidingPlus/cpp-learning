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
//coroutine-generator-iterator.cpp
//代码借鉴了：https://en.cppreference.com/w/cpp/language/coroutines

#include <coroutine>
#include <exception>
#include <iostream>

template <typename value_t>
class generator {
private:
    bool full = false; //允许是否生成新值的开关。为true时允许，否则禁止。这几乎是唯一的控制每次只生成一个值的方法。

    void _fill() {
        if (full) return; //禁止生成新值

        handle(); //调用句柄以生成新值
        if (handle.promise().exptr) //如果发生异常
            std::rethrow_exception(handle.promise().exptr); //向上下文广播异常

        full = true; //翻转开关
    }

public:
    using value_type = value_t;

    struct promise_type; //协程必须关联到一个promise对象上。这里是超前声明
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type { //这个promise类型是必须的，且必须是这个名字
        value_type value;
        std::exception_ptr exptr;

        generator get_return_object() { //promise_type类型中必须有这个成员
            return generator(handle_type::from_promise(*this));
        }

        std::suspend_always initial_suspend() { //promise_type类型中必须有这个成员
            return {};
        }

        std::suspend_always final_suspend() noexcept { //promise_type类型中必须有这个成员
            return {};
        }

        void unhandled_exception() { //promise_type类型中必须有这个成员
            exptr = std::current_exception(); //保存异常
        }

        template <std::convertible_to<value_type> from_type> //使用concept：from_type是可转换到value_type的
        std::suspend_always yield_value(from_type &&from) { //promise_type类型中必须有这个成员
            value = std::forward<from_type>(from); // 缓存结果到promise对象中
            return {};
        }

        void return_void() {} //promise_type类型中必须有这个成员
    };

    handle_type handle;

    generator(handle_type h) : handle(h) {}
    ~generator() {
        handle.destroy();
    }

    friend class iterator;
    class iterator { //迭代器的存在，将生成器伪装成一个容器
        using value_type = typename generator::value_type;

    private:
        generator *gen;

    public:
        iterator(generator *g = nullptr) : gen(g) {}

        bool operator!=(const iterator &) { //因只需判断生成器是否终止，不涉及迭代器，所以参数只起占位作用
            gen->_fill(); 
            return !gen->handle.done();
        }

        iterator &operator++() {
            gen->full = false; //允许产生新值
            return *this;
        }

        value_type operator*() {
            gen->_fill();
            return std::move(gen->handle.promise().value);
        }
    };

    iterator begin() {
        return iterator(this);
    }

    iterator end() {
        return iterator();
    }
};

using fibo_valtype = unsigned long;
generator<fibo_valtype> fibonacci(unsigned n) { //n不得大于94，否则将会导致值溢出
    if (n == 0) co_return; //如果n==0，本协程将不生成任何结果，直接结束

    co_yield 1;  //生成第一个值。此后本协程暂停在此处，等待恢复执行
    if (n == 1) co_return; //如果n==1，本协程将只生成一个结果，然后结束

    co_yield 1;  //生成第二个值。此后本协程暂停在此处，等待恢复执行
    if (n == 2) co_return; //如果n==2，现在已生成了两个结果，所以本协程该结束了

    fibo_valtype a = 1, b = 1, s;
    for (decltype(n) i = 3; i <= n; ++i) {
        s = a + b;
        a = b;
        b = s;
        co_yield s; //生成后续值。此后本协程暂停在此处，等待恢复执行
    }
}

generator<int> odd(int a, decltype(a) b) { //强制b的类型与a一样
    if (a <= b) //生成递增序列
        //o初始化为大于等于a的第一个奇数
        for (auto o = a + !(a & 1); o <= b; o += 2) co_yield o;
    else //生成递减序列
        //o初始化为小于等于a的第一个奇数
        for (auto o = a - !(a & 1); o >= b; o -= 2) co_yield o;
}

int main() {
    std::cout << "How many fibonacci numbers will be generated(<94)?";
    unsigned n;
    std::cin >> n;
    int i = 0;
    auto gen = fibonacci(n); //大于94会导致异常。这里们省略了处理代码
    for (auto e : gen)
        std::cout << "fib[" << ++i << "]=" << e << std::endl;

    std::cout << "\nPlease input a range:";
    int a, b;
    std::cin >> a >> b;
    std::cout << "The odd numbers between " << a << " and " << b << " are:" << std::endl;
    i = 0;
    for (auto e : odd(a, b)) //生成[a,b]之间的所有奇数
        std::cout << ++i << ": " << e << std::endl;

    return 0;
}