
mylib.js: mylib.cc
	emcc -std=c++11 $< -o $@ -s EXTRA_EXPORTED_RUNTIME_METHODS='["Pointer_stringify", "intArrayFromString", "ALLOC_NORMAL", "allocate", "cwrap"]'

clean:
	rm *.wasm mylib.js
