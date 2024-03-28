a=10
b=20

sum=`expr $a + $b`
echo "两数之和为：$sum"

mul=`expr $a \* $b`
echo "两数之和为：$mul"

a=10
b=20

if [ $a -eq $b ]
then
   echo "$a -eq $b : a 等于 b"
else
   echo "$a -eq $b: a 不等于 b"
fi
if [ $a -ne $b ]
then
   echo "$a -ne $b: a 不等于 b"
else
   echo "$a -ne $b : a 等于 b"
fi

a=10
b=20

if [ $a != $b ]
then
   echo "$a != $b : a 不等于 b"
else
   echo "$a == $b: a 等于 b"
fi 

a=10
b=20

if [[ $a -lt 100 && $b -gt 100 ]]
then
   echo "返回 true"
else
   echo "返回 false"
fi 

a="abc"
b="efg"

if [ $a != $b ]
then
   echo "$a != $b : a 等于 b"
else
   echo "$a != $b: a 不等于 b"
fi 


file="operator.sh"
if [ -r $file ]
then
   echo "文件可读"
else
   echo "文件不可读"
fi    
