if [ $# -ne 1 ] # 利用$#判断命令行有几个参数
then
        echo "Usage: usr_monitor username" # 参数不对就报错
        exit
fi
user_input=$1 # 将第一个参数赋给user_input
echo -e "You will monitor [$user_input]\n"
user=$(who)
username=`who |awk '{print $1}'` # 只截取登陆了的用户名
echo -e "Current user list is:\n$username\n"

compare=$(echo $username | grep "${user_input}") #获取username中与user_input相同的部分

while [ "$compare" == "" ]
do
        echo "waiting user [$user_input] ..."
        sleep 5
        username=`who |awk '{print $1}'`
        result=$(echo $username | grep "${user_input}")
done
echo "[$user_input] is log on"
