#!/bin/bash

num=0
sum=0

while true
do
	read -p "Please enter a number or Enter for exit: " num
	if [[ -z $num ]]; then
		break
	else 
		sum=$((sum + num))
	fi
done
echo -e "The sum of inputs is $sum\n"
