var mylib = require("./mylib.js");

mylib["onRuntimeInitialized"] = () => {
    let instance = new mylib.Vector(3, 4);
    console.log("Length is " + instance.length());
    console.log("Vector x is " + instance.x);
    // Explicito pq JS não chama o
    // destrutor automaticamente
    instance.delete();
};
