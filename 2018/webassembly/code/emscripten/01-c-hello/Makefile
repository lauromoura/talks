
hello.js: hello.c
	emcc $^ -o $@

hello-html.html: hello.c
	emcc $^ -o $@

clean:
	rm -f *.js *.wasm *.html
