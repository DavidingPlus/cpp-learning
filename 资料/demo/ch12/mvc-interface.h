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

//---------------------------------------------------------------------------
//MVC对象的标签类型
enum mvctag_t : unsigned { MODEL, VIEW, CONTROLLER, RENDERER, ROUTER };


//---------------------------------------------------------------------------
//MVC对象根类
template <mvctag_t mvctag>
struct mvc_obj {
    const mvctag_t tag = mvctag;
    virtual ~mvc_obj() {}
};


//---------------------------------------------------------------------------
//数据集接口定义
struct iDataset {
    const bool is_dataset = true;
};


//---------------------------------------------------------------------------
//MVC接口定义

//模型接口
struct iModel : public mvc_obj<mvctag_t::MODEL> {
    virtual const iDataset& query() const = 0; //模型查询接口
};

//视图接口
struct iView : public mvc_obj<mvctag_t::VIEW> {
    virtual void refresh() = 0; //视图刷新接口
};

//控制器接口
struct iController : public mvc_obj<mvctag_t::CONTROLLER> {
    struct action_t { unsigned next_action; }; //控制器动作类型
    virtual action_t get_user_response() const = 0; //获取用户响应
    virtual action_t action() = 0; //控制器动作接口
};

//路由器接口
struct iRouter : public mvc_obj<mvctag_t::ROUTER> {
    virtual void route(iController::action_t = {}) = 0; //路由接口
};

//渲染器接口
struct iRenderer : public mvc_obj<mvctag_t::RENDERER> {
    virtual void render() const = 0; //渲染接口
};


//---------------------------------------------------------------------------
//概念
template <typename T>
concept Dataset = requires { T::is_dataset; };

template <typename T>
concept Model = requires { T::tag == mvctag_t::MODEL; };

template <typename T>
concept Controller = requires { T::tag == mvctag_t::CONTROLLER; };

template <typename T>
concept View = requires { T::tag == mvctag_t::VIEW; };

template <typename T>
concept Router = requires { T::tag == mvctag_t::ROUTER; };

template <typename T>
concept Renderer = requires { T::tag == mvctag_t::RENDERER; };