function makeGreeter(greeting) {
    return function (name) {
        return (`${greeting} ${name} jan! Have a good day!`);
    } 
}
let f = makeGreeter("Good morning");
console.log(f("Davit"));