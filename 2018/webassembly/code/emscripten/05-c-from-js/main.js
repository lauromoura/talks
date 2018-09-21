
var mylib = require('./mylib.js');

mylib['onRuntimeInitialized'] = function() {
    console.log(mylib._factorial(6));

    var str = mylib.allocate(mylib.intArrayFromString("grite!!!!"), 'i8', mylib.ALLOC_NORMAL);
    var str_ret = mylib._allcaps(str);
    console.log(mylib.Pointer_stringify(str_ret));
};

