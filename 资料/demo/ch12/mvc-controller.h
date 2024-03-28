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

#include "mvc-view.h"

enum : unsigned { TERMINATE = 0, HOME }; //定义动作。这里仅列出部分，后续会扩展更多动作

template <View view_t>
struct controller : public iController {
    using view_type = view_t;
    using model_type = typename view_type::model_type;

    action_t action() override final { //最终覆盖action接口
        V.refresh(); //刷新视图
        return get_user_response();
    }

    controller() = delete;
    controller(const model_type &m) : V(m), M(m) {}
    
    action_t get_user_response() const override {
        return {HOME}; //默认动作
    }

protected:
    mutable view_type V;
    const model_type& M;
};
