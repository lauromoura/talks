
main.wat: main.wasm
	wasm2wat main.wasm -o main.wat

main.wasm: main.c
	emcc -Os main.c -o main.js -s WASM=1

clean:
	rm *.wasm *.wat *.js

