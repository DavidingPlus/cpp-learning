#example1 for read
echo -n "Input your name: "
read username
echo "Your name is $username"

#example2 for read
echo -n "Input date with format yyyy mm dd: "
read year month day
echo "Today is $year/$month/$day, right?"
echo -n "Press any key to confirm and continue"
read answer
echo "I know the date, bye!"
