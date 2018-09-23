
hello-sdl.html: hello-sdl.cpp
	emcc $^ -o $@ -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file native_floripa.png

hello-native: hello-sdl.cpp
	cc $^ -o $@ `pkg-config --cflags --libs SDL2_image sdl2`

clean:
	rm *.js *.wasm *.html *.data hello-native
