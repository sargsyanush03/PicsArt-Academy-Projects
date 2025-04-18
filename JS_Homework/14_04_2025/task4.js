console.log(`Welcome to game "Guess number"`);
console.log("Range: 1 - 10");

//random generates a random floating number in [0 , 1) range
//after multiplying the range is [0, 10)
//floor rounds down the floating number and converts to integer
//+ 1 for including 10

let real_answer = Math.floor(Math.random() * 10) + 1;
let answer;
const  readline = require('readline-sync');
do {
	console.log("Guess the number:");
	answer = readline.questionInt();
	if (answer < real_answer) {
		console.log("Too low");
	} else if (answer > real_answer) {
		console.log("Too high");
	} else {
		console.log("You guessed the number.\nCongrats🎉!");
		break;
	}
} while (answer != real_answer);
