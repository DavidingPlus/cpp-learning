echo "Hello World"

cout=1			# 定义变量		
name="ohuohuo"	# 定义变量
echo $cout		 # 取变量值
echo $name	     # 取变量值

DATE1=`date`	
DATE2=$(date)
echo $DATE1
echo $DATE2

name="test_name"
echo "My name is ${name} and you"

# Url="http://www.baidu.com"
# readonly Url
# Url="http://www.csnd.net"

name="ohuohuo"
Url="http://www.baidu.com"
readonly Url	# 设置可读变量
unset name3		# 可以被删除
unset Url		# 不可被删除
echo $name		# 不被打印出
echo $Url		# 打印出

