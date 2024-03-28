/* 
 * Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
 * 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2. 
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2 
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details. 
 */


#pragma once

//MVC的最终实现

#include <iostream>
#include <fstream>
#include <array>
#include <map>
#include <list>
#include <string>
#include <format>

using namespace std;

#include "mvc-model.h"
#include "mvc-view.h"
#include "mvc-controller.h"
#include "mvc-router.h"

//---------------------------------------------------------------------------
//定义终端显示颜色
const string red{"\033[91m"}, green{"\033[92m"}, amber{"\033[33m"}, 
    magenta{"\033[95m"}, turquoise{"\033[96m"}, ende{"\033[0m"};
const string colors[] = { green, amber, magenta, turquoise};


//---------------------------------------------------------------------------
//定义模型的基本数据类型：[Q1, Q2, Q3, Q4]
using data_type = array<unsigned, 4>;

//定义用于模型的抽象数据集类型
struct sales_dataset_type final : public iDataset, public map<unsigned, data_type> {};

//定义用于渲染的数据集类型
struct sales_r_dataset_type final : public iDataset, public list<string> {};


//---------------------------------------------------------------------------
//最终的模型类型。从.txt文件获取数据
struct sales_model final : public model<sales_dataset_type> {
    sales_model(string db_file) {
        fstream f(db_file);
        unsigned year;
        data_type q;

        while (!f.eof()) {
            f >> year >> q[0] >> q[1] >> q[2] >> q[3];
            DS.emplace(year, q);
        }
        f.close();
    }

    sales_model(const sales_model&) = delete; //禁止复制
    sales_model(sales_model&&) = delete; //禁止转移。两个禁止保证在运行时，sales_model模板类只能有一个实例
};


//---------------------------------------------------------------------------
//最终的渲染器类型：字符终端
struct console final : public renderer<sales_r_dataset_type> { 
    void render() const override {
        for (auto &s : RDS) cout << s << endl;
    }

protected:
    void clear_dataset() override {
        RDS.clear();
    }
};


//---------------------------------------------------------------------------
//最终的视图类型：基类
struct sales_view : public view<sales_model, console> {
    using view<sales_model, console>::view;
};

//主视图类
struct sales_view_home final : public sales_view {
    using sales_view::sales_view;

protected:
    void format_dataset(const dataset_type &, r_dataset_type &R) override {
        R.emplace_back("Please choose an option:");
        R.emplace_back("1. show table");
        R.emplace_back("2. show bar-chart(by year)");
        R.emplace_back("3. exit");
    }
};

//出错用视图
struct sales_view_error final : public sales_view {
    using sales_view::sales_view;

protected:
    void format_dataset(const dataset_type &, r_dataset_type &R) override {
        R.emplace_back("Invalid option. please choose 1~3.\n\n");
    }
};

//表格视图
struct sales_view_table final : public sales_view {
    using sales_view::sales_view;

protected:
    void format_dataset(const dataset_type &M, r_dataset_type &R) override {
        R.emplace_back("\nyear\tQ1\tQ2\tQ3\tQ4\n----------------------------------");
        for (auto &[y, q] : M)
            R.emplace_back(format("{}\t{}\t{}\t{}\t{}", y, q[0], q[1], q[2], q[3]));
        R.emplace_back("\n");
    }
};

//柱状图视图
struct sales_view_bar final : public sales_view {
    using sales_view::sales_view;

protected:
    void format_dataset(const dataset_type &M, r_dataset_type &R) override {
        string s;
        for (auto &[y, q] : M) {
            for (unsigned i = 0; i < q.size(); ++i) {
                string t;
                for (unsigned j = 0; j < q[i]; ++j) t.push_back('*');
                s = format("{} Q{}|{}{}{}", i == 0 ? to_string(y) : "    ", i + 1, colors[i], t, ende);
                R.emplace_back(s);
            }
            R.emplace_back(" ");
        }
    }
};


//---------------------------------------------------------------------------
enum : unsigned { TABLE = HOME + 1, BAR, ERROR, END }; //扩充动作

//最终的控制器类型
template <View view_t>
struct sales_controller final : public controller<view_t> {
    using controller<view_t>::controller;
};

//特化的控制器类型
template <>
struct sales_controller<sales_view_home> final : public controller<sales_view_home> {
    using controller<sales_view_home>::controller;

    action_t get_user_response() const override {
        unsigned op;
        cin >> op;
        switch (op) {
        case 1:
            return {TABLE};
        case 2:
            return {BAR};
        case 3:
            return {TERMINATE};
        }

        return {ERROR};
    }
};


//---------------------------------------------------------------------------
//最终的路由器类型
template <unsigned len>
struct sales_router final : public router<len> {
    using router<len>::router;
    using router<len>::route_table;
    
    void route(iController::action_t a = {HOME}) override {
        do {
            a = route_table[a.next_action]->action();
        } while (a.next_action != TERMINATE);
    }
};
