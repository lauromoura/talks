
files.js: files.c
	emcc $^ -o $@

files_fixed.html: files.c tests/input.txt
	emcc $< -o $@ --preload-file tests/input.txt

clean:
	rm -f *.js *.wasm *.html *.data
