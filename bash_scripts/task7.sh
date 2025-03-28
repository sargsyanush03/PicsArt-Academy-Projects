#!/bin/bash

reply="y"
while [[ $reply == "y" ]]
do
	read -p "Enter the first number: " num1
	read -p "Enter the second number: " num2
	read -p "Enter the operation: " opcode

	if [[ $opcode == "+" ]]; then
		echo "$((num1 + num2))"
	fi
	if [[ $opcode == "-" ]]; then
		echo "$((num1 - num2))"
	fi
	if [[ $opcode == "*" ]]; then
		echo "$((num1 * num2))"
	fi
	if [[ $opcode == "/" ]]; then
		if ((num2 == 0)); then
			echo "Division by 0 is not allowed"
		else
			echo "$((num1 / num2))"
		fi
	fi
	if [[ $opcode == "%" ]]; then
		if ((num2 == 0)); then
			echo "Division by 0 is not allowed"
		else
			echo "$((num1 % num2))"
		fi
	fi
	read -p "Do you want to try again? y? n?  " reply
	if [[ $reply != "y" ]]; then
		break
	fi
done
