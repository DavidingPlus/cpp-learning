# Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
# 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2. 
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2 
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the Mulan PSL v2 for more details. 

# cxx、sources、options、libs、module等变量由make的命令行传入。例如：
# make cxx=g++ sources="./1.cpp ./2.cpp" libs="" module=-fmodules-ts
# make clean clean=rm target=a.out

all:
	@$(cxx) $(sources) $(options) $(libs)

.PHONY: clean

clean:
	@$(clean) $(target)