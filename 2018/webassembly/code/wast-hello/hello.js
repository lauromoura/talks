
const fs = require('fs');
const buf = new Uint8Array(fs.readFileSync('hello.wasm'));

WebAssembly.instantiate(buf, {}).then(obj =>
    console.log(obj.instance.exports.addTwo(3, 2))
);

