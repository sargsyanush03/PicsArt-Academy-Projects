function createCounter() {
    let count = 0;
    return function () {
        return count++;
    };
}
let c = createCounter();
console.log(c());
console.log(c());
console.log(c());
console.log(c());

