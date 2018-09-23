
mylib.js: mylib.cpp
	emcc --bind --std=c++11 $< -o $@

clean:
	rm -f mylib.js *.wasm *.html
