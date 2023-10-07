# 与redefine-member.cpp结果做对比
class base:
    name: str

    def __init__(self) -> None:
        self.name = 'base'

    def whoami(self) -> None:
        print(self.name)


class derived(base):
    name: str  # 在python里面重定义对象的话，子类同名对象就会覆盖掉父类的，与C++不同

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
