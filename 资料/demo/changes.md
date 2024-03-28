## 更新日志

---

2023/9/07

#### 一、仓库更新
1. 新增了`demo/lb`子目录：
	- `lb/dlist`子目录：今天上课的编码
	- 这意味着构建命令是： 
		- zmake
		```bash
		zmake -b lb/dlist
		```
		- g++
		```bash
		g++ -std=c++23 -fsanitize=address lb/dlist/testdlist.cpp
		```
		- MinGW
		```Powershell
		g++ -std=c++23 lb\dlist\testdlist.cpp
		```
	- 建议你在`mine`下建立一个子目录`dlist`，然后将今天的代码移动到里面。构建命令是与上面的类似，只不过把`lb`改成`mine`

2. 将脚本`zmake`中使用`py`的地方改成了`python3`；将脚本`zmake.ps1`中使用`py`的地方改成了`python`

3. 去掉了`.zmake/zmake.py`中对`3.11`版本的依赖

### 二、复预习

教材：《C++程序设计--现代方法》，白忠建编著，人民邮电出版社。
    
1. 第三章 类：面向对象的基石

	难重点：
	- 类的概念：语法
	- 类对象的实例化和初始化
	- 构造函数和析构函数

### 三、预习
    
1. 第四章 类的高级特性

	难重点：
	- 复制控制

### 四、练习
1. 根据老师的博客`https://baizj.gitee.io`配置编程环境并练习使用。
2. 使用zmake构建应用并阅读源代码。注：zmake也能在Windows下使用

---

2023/9/04

### 一、仓库更新
1. 修改了`demo\tool`目录下的几个文件。

---

2023/7/27

### 一、仓库更新
1. 新增`demo\tool`目录。其中的子目录和文件有：
	- mksysmod：编译生成系统头文件对应模块的`Shell`脚本
	- mksysmod.ps1：编译生成系统头文件对应模块的`Powershell`脚
	- mkgcms：编译生成多个系统头文件对应模块的`Shell`脚本
	- mkgcms.ps1：编译生成多个系统头文件对应模块的`Powershell`脚

	>注：上述文件原来在demo目录下

2. 除了以下文件和目录：
    - ch1/helloworld.cpp
    - ch3/case
	其它所有源代码中的"import"全部改成了"include"。

3. `JSON`格式的配置文件`.zmake/zmake-configure.json`改为更容易阅读的`YAML`格式的`.zmake/zmake-configure.yaml`。

4. 修改了`.zmake/zmake.py`以适应上述改动。

---

2023/7/15

### 一、仓库更新
1. 新增`demo`目录。其中的子目录和文件有：
	- .zmake：辅助构建工具
	- ch1：第一章示例
	- ch2：第二章示例
	- ch3：第三章示例
	- Makefile
	- mksysmod：编译生成系统头文件对应模块的`Shell`脚本
	- mksysmod.ps1：编译生成系统头文件对应模块的`Powershell`脚本
	- README.md：请先阅读此文件
	- zmake：启动辅助构建工具的`Shell`脚本
	- zmake.ps1：启动辅助构建工具的`Powershell`脚本

2. 新增`PPT`目录。其中包含所有章节和微课的演示文档。

>注：以上内容可能会有更改。请注意老师发布的信息。

### 二、预习

教材：《C++程序设计--现代方法》，白忠建编著，人民邮电出版社。

1. 第一章 引言
   
	难重点：
	- 面向对象的核心概念：数据封装、继承和多态
	- 编程范式：泛型

2. 第二章 C++：一个更好的C

	难重点：
	- 引用：左值引用和右值引用
	- 类型自动推导
	- new和delete运算符
	- lambda表达式
	- 异常处理机制
	- 函数：函数类型、函数重载
    
3. 第三章 类：面向对象的基石

	难重点：
	- 类的概念：语法
	- 类对象的实例化和初始化
	- 构造函数和析构函数
   
### 三、练习
1. 根据老师的博客`https://baizj.gitee.io`配置编程环境并练习使用。
2. 使用zmake构建应用并阅读源代码。
