# LaoBai_Cpp_Mine

老白`cpp`课程的学习记录.

关于`zmake`工具：

- 编译单个文件就：

  ```bash
  ./zmake -b test.cpp # test.cpp是源文件
  ```

- 编译整个目录的所有文件就：

  ```bash
  ./zmake -b dir/ # dir/是源目录
  ```

  这里不需要加上具体的文件名，给目录就可以，会自动编译链接所有的源文件
