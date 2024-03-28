num=0
for i in {1..9}
do 
    num=`expr $num + 1`
done

echo $num
echo

#计算1-100奇数之和
sum=0
i=1
while [ $i -le 100 ]
do
    sum=`expr $sum + $i`
    i=`expr $i + 2`
done
echo "1-100的奇数和为:$sum"

sum=0
for ((i=1;i<100;i+=2))
do
    let sum=$sum+$i
done
echo "1-100的奇数和为:$sum"
