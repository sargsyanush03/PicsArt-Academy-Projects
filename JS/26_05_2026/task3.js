function createVault(secretKey) {
    let key = secretKey;
    return {
        getSecret: function () {return key},
        setSecret: function (newKey) {
            key = newKey;
        }
    }
}
let c = createVault("Anush");
console.log(c.getSecret());
c.setSecret("new");
console.log(c.getSecret());
console.log(c.secretKey);