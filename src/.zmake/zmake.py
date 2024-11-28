# Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
# 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2. 
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2 
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the Mulan PSL v2 for more details. 


import os
import sys
import yaml
from typing import TypedDict, NoReturn, Callable #, Required


# 类型定义

# 定义配置类型
class config_t(TypedDict, total = False):
    # cmd: Required[str] # 编译器名，例如：g++、clang++
    # options: Required[str]  # 编译参数，例如：-g -Wall
    # clean: Required[str]    # 删除命令的名字，例如：rm、del
    # target: Required[str]   # 可执行代码的名字，例如：a.out、a.exe
    cmd: str # 编译器名，例如：g++、clang++
    options: str  # 编译参数，例如：-g -Wall
    clean: str    # 删除命令的名字，例如：rm、del
    target: str   # 可执行代码的名字，例如：a.out、a.exe


# 定义类型
arg_t = str | int
action_t = tuple[Callable[[config_t, arg_t], int | NoReturn], arg_t]


# 颜色常量
grey = "\033[90m"
red = "\033[91m"
green = "\033[92m"
turquoise = "\033[96m"
ende = "\033[0m"


# 版本号
VERSION = {
    'major': 1,
    'minor': 0,
    'bugfix': 0
}


def error(errcode: int, arg: str) -> NoReturn:
    """
    错误处理，结束程序

    @param  option：string 无效的命令行选项
    @return never
    """

    errmsg = [
        f'{red}无效的选项"{arg}"{ende}。\n运行 "zmake -h" 显示帮助信息',
        f'{red}指定的源文件或者源目录 {arg} 不存在{ende}'
    ]
    print(errmsg[errcode])
    exit(1)


def usage(_: config_t, u: int = 0) -> NoReturn:
    """
    显示帮助，结束程序
    
    @param  _ 无用占位参数
    @param  u int：选择哪种信息。0：帮助，1：版本。默认参数
    @return never
    """

    usage_msg = [
        f'''用法:
    zmake -bchv [source]
选项:
    -b <source>     编译链接<source>，构建应用。例如：
                    {turquoise}zmake -b ch1/helloworld.cpp{ende}
                    {grey}注：<source>可以是单个源文件名，也可以是目录名。{ende}
    -c              清除可执行代码。此选项无参数
    -h              显示帮助信息。此选项无参数
    -v              显示版本号。此选项无参数
''',

        f'''zmake Version {turquoise}{VERSION["major"]}.{VERSION["minor"]}.{VERSION["bugfix"]}{ende}
{grey}Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2. 
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2 
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. {ende}'''
]

    print(usage_msg[u])
    exit(1)


def build_all(config: config_t, src: str) -> int | NoReturn:
    """
    构建默认任务。此函数依赖于make工具和预先写好的makefile
    
    @param  config config_t，配置参数
    @param  src  str：源文件或者源目录名
    @return int，make程序的退出码。源文件不存在则不返回。
    """

    def make_source_list(path: str) -> str | NoReturn:
        """
        生成编译命令行所需的源文件列表
        
        @param  path string：源文件或者源目录名
        @return str：源文件列表串
        """

        if not os.path.exists(path): error(1, path)

        srclist = path
        # 如果path是目录，则需要编译链接该目录下的所有cpp源文件
        if os.path.isdir(path): 
            files = []
            for file in os.listdir(path):
                _, ext = os.path.splitext(file)
                if ext in ['.cpp']: 
                    files.append(os.path.join(path, file))
            # 必须将模块源文件放在cpp文件前，并且要按依赖顺序排序。这里用文件名作为依赖依据
            # 源文件排列的顺序是：模块接口.cpp 模块实现.cpp 使用模块的源文件.cpp
            srclist = ' '.join(sorted(files))
        return srclist

    sources = make_source_list(src)

    cxx = config['cmd']
    options = config['options']
    libs = '' # if not conf['libs'] else conf['libs']
    target = config['target']
    
    print(f'正在构建 {turquoise}{target}{ende}...')
    r = os.system(f'make cxx={cxx} sources="{sources}" options="{options}" libs="{libs}"')
    if r == 0: print(f'构建完成。运行 {turquoise}{target}{ende} 观察结果')
    return r


def build_clean(config: config_t, _: None) -> int:
    """
    执行清理任务，删除指定的可执行代码。此函数依赖于make工具和预先写好的makefile
    
    @param  conf config_t，配置参数
    @param  _，无用的占位参数
    @return int，make程序的退出码
    """

    clean = config['clean']
    target = config['target']
    return os.system(f'make clean clean={clean} target={target}')


def parse_args() -> tuple[str, str | None]:
    """
    解析命令行参数
    
    @param  None
    @return tuple(操作代码, 参数)
    """

    # 截掉原始的argv[0]，因为那是程序本身的名字。
    # 后argv仅包含命令行参数。如果运行时没有给出参数，那么该数组为空，argc得到0
    argv = sys.argv[1:]
    argc = len(argv)

    src = None
    match argc:
        case 1:
            option = argv[0]
            if option in ['-h', '-v', '-c']: 
                code = option[1]
            else: 
                error(0, option)
        case 2:
            option = argv[0]
            code = 'b'
            if option in ['-b']: 
                src = argv[1]
            else: 
                error(0, option)
        case _:
            code = 'h'

    return (code, src)


def set_config(code: str, src: str) -> config_t:
    """
    载入配置
    
    @param  code  str，操作代码
    @param  src  str，源代码名
    @return config_t
    """


    # 载入配置文件
    with open(os.path.join('.', '.zmake', 'zmake-configure.yaml')) as f:
        gconfig: dict = yaml.safe_load(f)

    # 找到活动配置项
    active = 'mingw' if 'windir' in os.environ.keys() else gconfig['active']

    config = gconfig['compiler'][active]
    if code not in ['b']: return config

    opts = gconfig['options']
    # 组合编译链接选项
    cxxflag = opts['cxxflag']
    options = opts[config['options']]

    feature = gconfig['feature-applied']
    # 将Windows的路径分隔符\改成通用的/，并去掉路径开头的./
    src = src.replace('\\', '/').replace('./', '')
    path, _ = os.path.split(src)

    if active != 'mingw': # Windows环境目前不支持任何类型的消毒器
        # 如果项目使用线程消毒器选项。注：线程消毒器不能和内存消毒器一起使用
        if path in feature['tsan'] or src in feature['tsan']:
            print(f'这个应用的构建将使用{red}线程消毒器{ende}')
            options = opts['tsan']

    modu = ''
    # 如果项目启用了C++模块特性
    if path in feature['module'] or src in feature['module']:
        print(f'这个应用的构建将使用{red}C++ module特性{ende}')
        modu = opts['module']
    
    config['options'] = ' '.join([cxxflag, options, modu])

    return config


def main() -> int:
    """
    主函数
    """

    code, src = parse_args()
    config = set_config(code, src)

    # helper列表。指定选项的处理函数及其参数
    helper: dict[str, action_t] = {
        'b': (build_all, src),
        'c': (build_clean, None),
        'h': (usage, 0),
        'v': (usage, 1)
    }

    func, arg = helper[code]
    func(config, arg)

    return 0


# 启动程序
if __name__ == '__main__':
    main()
