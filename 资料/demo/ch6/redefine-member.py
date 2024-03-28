#
# Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
# 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the Mulan PSL v2 for more details.
#

# 与redefine-member.cpp结果做对比

class base:
    name: str

    def __init__(self) -> None:
        self.name = 'base'

    def whoami(self) -> None:
        print(self.name)

class derived(base):
    name: str

    def __init__(self) -> None:
        self.name = 'derived'

    def get_name(self) -> str:
        return self.name
    
if __name__ == '__main__':
    d = derived()
    d.whoami()
    print(d.get_name())

# 程序的输出应该类似于：
# derived
# derived

# 而对应cpp的输出应该是：
# base
# derived

# 请问这说明什么问题呢？