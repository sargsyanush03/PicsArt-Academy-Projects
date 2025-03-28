#!/bin/bash

real_answer=paris
user_answer=0
reply="y"
while [[ "$reply" == "y" ]]
do
	echo "The capital of France?"
	read user_answer
	if [[ "$(echo "$user_answer" | tr '[:upper:]' '[:lower:]')" == "$real_answer" ]]; then
		echo -e "Correct!\nDo you want to answer the same question again? :)"
		echo -e "Enter y - for yes, n - for no."
		read reply
	else 
		echo "The right answer is Paris"
	fi
	if [[ $reply == "n" ]]; then
		break
	fi
done
