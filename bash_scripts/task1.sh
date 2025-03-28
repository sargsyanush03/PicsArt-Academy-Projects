#!/bin/bash

read -p "Please enter the number: " num

if [[ "$num" =~ ^-?[0-9]+$ ]]; then
	if ((num % 2 == 0 )); then
		echo "Even"
	else
		echo "Odd"
	fi
else 
	echo "Invalid input!"
fi
