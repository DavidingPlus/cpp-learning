/*
 * Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
 * 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */


//bzj^_^
//isp-editor.cpp

#include <iostream>
#include <map>
#include <string>
using namespace std;

namespace code_editor {
static map<string, string> test_data{
    {"helloworld.cpp", "import <iostream>;\nint main()\n{\n\tstd::cout << \"Hello, world!\" << std::endl;\n\treturn 0;\n}\n"},
    {"helloworld.js", "console.log(\"Hello, world!\");"}
};

using plaintext = string;

using tool = string;
using path = string;
using tool_collection = map<tool, path>;

using language = string;
using toolchains = map<language, tool_collection>;

using shortcuts = map<string, string>;

class editor {
protected:
    string filename;
    plaintext code;
    toolchains tc;
    shortcuts sc;
    language lang;

public:
    editor(const toolchains &t, const shortcuts &s) : tc(t), sc(s) {}
    editor &edit() {
        cout << "+++ editing..." << endl;
        cout << code << endl;
        return *this;
    }
    editor &open(string fn) {
        cout << "+++ opening..." << endl;
        code = test_data[fn];
        filename = fn;
        lang = fn.substr(fn.find(".") + 1);
        if (lang == "cpp") lang = "c++";
        return *this;
    }
    editor &save() {
        cout << "+++ saving code into file " << filename << endl;
        return *this;
    }
    editor &launch(string key) {
        cout << key << " pressed. \n+++ launching " << lang << " " << sc[key] << " from "
            << (tc[lang])[sc[key]] << endl;
        return *this;
    }
};
};

using namespace code_editor;

int main() {
    editor e({
        {"c++", {{"compiler", "/usr/local/gcc/g++"}, {"debugger", "/usr/local/gcc/gdb"}}},
        {"js", {{"interpreter", "/usr/local/node/node"}}}
    }, {{"F10", "compiler"}, {"F11", "debugger"}, {"F12", "interpreter"}});

    e.open("helloworld.cpp").edit().save().launch("F10").launch("F11");
    cout << endl;
    e.open("helloworld.js").edit().save().launch("F12");

    return 0;
}