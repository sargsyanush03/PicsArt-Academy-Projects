function limitCalls(fn, n) {
    let count = 0;
    return function() {
        if(count === n) 
            return ('The number of calls has been exhausted');
        count++;
        console.log(count);
        return fn();
    }
}

function fn() {
    return ("Fn finished it's work!")
}

let c = limitCalls(fn, 3);
console.log(c());
console.log(c());
console.log(c());
console.log(c());
console.log(c());


