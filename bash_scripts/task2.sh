#!/bin/bash

input=0

while true 
do 
	echo "Enter exit for quiting..."
	read input
#convert input to lowercase and then compare
	if [[ "$(echo "$input" | tr '[:upper:]' '[:lower:]')" == "exit" ]]; then
		break
	else 
		echo "Your input is $input."
	fi 
done
