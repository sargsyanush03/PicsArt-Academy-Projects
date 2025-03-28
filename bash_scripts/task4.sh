#!/bin/bash

num=1
until (($num == 42))
do	
	read -p "Please enter 42! :  " num
	if (($num != 42)); then
		echo "Try again!"
	fi 
done
echo "Correct"
