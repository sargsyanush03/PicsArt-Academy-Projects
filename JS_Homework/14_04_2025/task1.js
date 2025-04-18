function print_value(value) {
	console.log(value + " - " + typeof value + ".\n");
}

var number = 10;
var string = "hello";
var bool = true;
var x = null;
var undef;

print_value(number);
print_value(string);
print_value(bool);
print_value(x);
print_value(undef);
