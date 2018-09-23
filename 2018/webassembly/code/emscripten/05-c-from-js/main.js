
var mylib = require('./mylib.js');

mylib['onRuntimeInitialized'] = function() {
    console.log("Chamada direta com inteiros");
    console.log(mylib._factorial(6));

    // https://kripken.github.io/emscripten-site/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html#call-compiled-c-c-code-directly-from-javascript
    console.log("Chamada direta com strings");
    let str = mylib.allocate(mylib.intArrayFromString("grite!!!!"),
                             'i8',
                             mylib.ALLOC_NORMAL);
    let str_ret = mylib._allcaps(str);
    console.log(mylib.Pointer_stringify(str_ret));
    mylib._free(str);
    mylib._free(str_ret);

    console.log("Chamada através de cwrap");
    let wrapped = mylib.cwrap("allcaps", "string", ["string"]);
    console.log(wrapped("oi cwrap"));


};

