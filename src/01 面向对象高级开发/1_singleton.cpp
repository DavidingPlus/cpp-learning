#include <iostream>
#include "1_Stu.h"

int main()
{
    // 单例设计模式
    // 构造函数在private里面 整个类是放在static堆区的 所有用户只用一份这个类的数据
    Stu::getInstance().setup(); // 这样就创造出来了一个类 并且是静态变量!!!程序共享这一份
    Stu2::getInstance().setup();

    return 0;
}