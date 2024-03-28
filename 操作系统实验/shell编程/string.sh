name="hello world"
str="This is a sentense $name"
echo $str

string="abcd"
echo "The length of the str is ${#string}" # 输出 4

string="this is a test"
echo ${string:2:6} # 表示从第3个字符开始截取

string="this is a test"
echo `expr index "$string" it`  # 输出 1
