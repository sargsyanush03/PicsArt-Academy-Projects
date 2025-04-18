console.log("Numbers from 1 to 20");
let i;
for (i = 1; i <= 20; ++i) {
	console.log(i);
}

console.log("Even numbers from 1 to 20");
i = 1;
while (i <= 20) {
	if (i % 2 == 0) {
		console.log(i);
	}
	++i;
}


//inport a Node.js module for synchronous reading
//the function returns an object and methods
const readline = require("readline-sync");
do {
	console.log("Enter a number (0 for exiting)...");
	//the next line requires an integer input from user
	i = readline.questionInt();
} while(i != 0);
console.log("Exiting program...");
