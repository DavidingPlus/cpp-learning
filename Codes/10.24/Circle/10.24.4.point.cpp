#include "10.24.4.point.h"

//设置x
void Point::setX(int x) //需要告诉是Point作用域下的成员函数!
{
    m_X = x;
}
//获取x
int Point::getX()
{
    return m_X;
}
//设置y
void Point::setY(int y)
{
    m_Y = y;
}
//获取y
int Point::getY()
{
    return m_Y;
}
