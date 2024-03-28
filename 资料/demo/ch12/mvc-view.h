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

#include "mvc-model.h"
#include "mvc-renderer.h"

template <Model model_t, Renderer renderer_t>
struct view : public iView {
    using model_type = model_t;
    using renderer_type = renderer_t;

    using dataset_type = typename model_type::dataset_type;
    using r_dataset_type = typename renderer_type::r_dataset_type;

    void refresh() override final { //最终覆盖刷新接口
        format_dataset(M.query(), R()); //将抽象数据集格式化为渲染用数据集
        R.render(); //渲染视图
    }

    view() = delete;
    view(const model_type &m) : M(m) {}

protected:
    const model_type &M;
    mutable renderer_type R;

    //将抽象数据集格式化为渲染用数据集的接口
    virtual void format_dataset(const dataset_type &, r_dataset_type &) = 0;
};