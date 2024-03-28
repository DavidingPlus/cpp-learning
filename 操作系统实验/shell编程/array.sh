array=(1.2 2 3 "helloworld")

value=${array[0]}
echo $value
echo ${array[@]} #读取所有!!!

# 取得数组元素的个数
length=${#array[@]}	# 从头到尾取
echo $length
# 或者
length=${#array[*]}	# 取所有
echo $length
# 取得数组单个元素的长度
lengthn=${#array[3]}	# 取特定
echo $lengthn
