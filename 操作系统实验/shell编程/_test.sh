date

cat 1_test.txt
echo

a=date
echo $a

b=`date`
echo -n $b
echo

c="fuck y"
echo "$cou" #未定义的字符串会用空串代替
echo "${c}ou"
