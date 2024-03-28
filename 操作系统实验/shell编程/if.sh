#The statement of if…then…fi (注释语句)
# if [ -f $1 ] # (测试命令行第一个参数是否为文件)
# then
# 	echo "File $1 exists." # (引用变量值)
# else
#     echo "File $1 does not exist."
# fi

# if [ -d $1 ] # (测试参数是否为目录)
# then 
# 	echo "File $1 is a directory" # (引用变量值)
# else
#     echo "File $1 is not a directory"
# fi

#The statement of if…then…else…fi
if [ -d $1 ]
then
	echo "$1 is a directory"
	exit # (立即退出当前的shell程序)
else 
	if [ -f $1 ]
	then
		echo "$1 is a common file"
	else
		echo "unknown" 
	fi
fi
echo "finish"
