#!/bin/bash

print_text_for_user () {
	echo "Please suggest a password"
	echo "-------------------------"
	echo "1.At least 8 characters length."
	echo "2.At least one digit and special character"
	echo "3.At least one uppercase and lowercase letter."
}

password=0
password_validation_test () {
	if ((${#password} >= 8)); then
			if [[ $password =~ [A-Z]+ ]]; then 
				if [[ $password =~ [a-z]+ ]]; then
					if [[ $password =~ [0-9]+ ]]; then
						if [[ $password =~ [[:punct:]]+ ]]; then
							echo "Password is created successfully: $password"
							break
						else 
							echo "Password doesn't contain a special character.Try again."
						fi		
					else
						echo "Password doesn't contain a digit.Try again."
					fi 
				else
					echo "Password doesn't contain a lowercase letter.Try again."
				fi
			else
				echo "Password doesn't contain an uppercase letter.Try again."
			fi
		else
			echo "Password contain less than 8 characters.Try again."
		fi
}

#main program
############################################
	print_text_for_user
	while true
	do
		read -s password
		password_validation_test
	done
	echo -e "Let's check, do you remember it :) \nEnter your password: "
	i=0
	while (( i != 4 ))
	do
		if ((i >= 1)); then 
			echo "You have only $((4 - i)) attempt opportunity"
		fi
		read -s check_value
		if [[ "$password" == "$check_value" ]]; then
			echo "The password is correct."
			break
		else
			echo "Wrong password.Try again."
		fi
		((++i))
	done
############################################
