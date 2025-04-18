process.stdin.on('data', function(data) {
	let age = parseInt(data.toString().trim());
	if (age < 18) {
		console.log("You are a minor.");
	} else if (age >= 18) {
		if (age >= 65) {
			console.log("You are a senior citizen.");
		} else {
			console.log("You are an adult.");
		}
	}
	process.exit();
});

