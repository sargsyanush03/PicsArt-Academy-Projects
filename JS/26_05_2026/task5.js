function createMultiplier(x) {
    return function(num) {
        return num * x;
    }
}

let f = createMultiplier(10);
console.log(f(5));
console.log(f(7));
