clear
echo "Input file name:"
read fname
if [ -f $fname ]
then
    ls -l $fname
else
    echo "Can't find the file $fname"
    exit
fi
oldstate=`ls -l $fname|awk '{print $5}'`
change=0
test=0
while [ "$change" -ne 2 ] && [ "$test" -ne 10 ]
do
    newstate=`ls -l $fname|awk '{print $5}'`
    if [ "$oldstate" -eq "$newstate" ]
    then
        echo "test file $fname's status ..."
        test=`expr $test + 1`
    else
        echo "file $fname's changed!"
        oldstate=$newstate
        change=`expr $change + 1`
        test=0
    fi
    sleep 1 #每隔多少秒检测一次
done
if [ $change -eq 2 ]
then
    echo "File has changed twice then exit."
    exit
else
    echo "Times over then exit."
    exit
fi
