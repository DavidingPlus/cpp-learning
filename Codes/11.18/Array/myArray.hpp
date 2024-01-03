//自己的通用的数组类
#pragma once
#include <iostream>
using namespace std;

template <typename T>
class MyArray
{
public:
    MyArray() {}
    //有参构造 参数 容量
    MyArray(int capacity) : m_Capacity(capacity), m_Size(0), pAddress(new T(this->m_Capacity)) {}

    //尾插法
    void Push_Back(const T &val)
    {
        //判断容量是否等于大小
        if (this->m_Size == this->m_Capacity)
            return;
        this->pAddress[this->m_Size] = val;
        ++this->m_Size; //更新数组大小
    }

    //尾删法
    void Pop_Back()
    {
        //判断容量是否为空
        if (this->m_Size == 0)
            return;
        //让用户访问不到最后一个元素,即为尾删,逻辑删除
        --this->m_Size;
    }

    //通过下标方式访问数组中的元素
    T &operator[](int index)
    {
        return this->pAddress[index];
    }

    //返回数组的容量
    int getCapacity() { return this->m_Capacity; }

    //返回数组的大小
    int getSize() { return this->m_Size; }

    //析构函数
    ~MyArray()
    {
        if (pAddress)
        {
            // cout << "MyArray析构函数调用" << endl;
            delete[] this->pAddress;
            this->pAddress = nullptr;
        }
    }

    //拷贝构造
    MyArray(const MyArray &arr)
    {
        // cout << "MyArray拷贝构造调用" << endl;

        this->m_Capacity = arr.m_Capacity;
        this->m_Size = arr.m_Size;

        //深拷贝
        this->pAddress = new T[arr.m_Capacity];
        //将arr中的数据拷贝过来
        for (int i = 0; i < arr.m_Size; ++i)
        {
            this->pAddress[i] = arr.pAddress[i];
        }
    }

    //重载=运算符 防止浅拷贝
    MyArray &operator=(const MyArray &arr)
    {
        // cout << "MyArray operator= 调用" << endl;

        //先判断原来堆区是否有数据 如果有显示放
        if (this->pAddress)
        {
            delete[] this->pAddress;
            this->pAddress = nullptr;
            this->m_Capacity = 0;
            this->m_Size = 0;
        }

        //深拷贝
        this->m_Capacity = arr.m_Capacity;
        this->m_Size = arr.m_Size;
        this->pAddress = new T[arr.m_Capacity];
        //将arr中的数据拷贝过来
        for (int i = 0; i < arr.m_Size; ++i)
        {
            this->pAddress[i] = arr.pAddress[i];
        }
        return *this;
    }

private:
    T *pAddress;    //指针指向堆区开辟的真实数组
    int m_Capacity; //数组容量
    int m_Size;     //数组大小
};
