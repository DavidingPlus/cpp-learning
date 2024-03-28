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

#include <memory>

#include "mvc-controller.h"

template <unsigned len>
struct router : public iRouter {
    template <Controller controller_t, Model model_t>
    void register_controller(unsigned entry, const model_t& model) { //注册控制器
        route_table[entry] = std::make_unique<controller_t>(model);
    }

    router() = default;
    router(const router&) = delete; //禁止复制
    router(router&&) = delete; //禁止转移。两个禁止保证在运行时，router模板类只能有一个实例

protected:
    //路由表。表项是指向控制器的唯一智能指针
    std::unique_ptr<iController> route_table[len]; 
};
