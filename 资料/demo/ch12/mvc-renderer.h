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

#include "mvc-interface.h"

template <typename r_dataset_t>
struct renderer : public iRenderer {
    using r_dataset_type = r_dataset_t; //用于渲染的数据集类型

    r_dataset_type& operator()() {
        clear_dataset();
        return RDS;
    }

protected:
    mutable r_dataset_type RDS; //渲染用的数据集由模型数据集格式化得到

    virtual void clear_dataset() = 0;
};
