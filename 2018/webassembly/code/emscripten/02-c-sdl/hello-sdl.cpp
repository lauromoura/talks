#include <stdio.h>
#include <SDL/SDL.h>

#include <algorithm>
#include <string>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

extern "C" int main() {

    // STL Too!
    std::string str("Starting SDL demo");
    std::transform(str.begin(), str.end(), str.begin(), &toupper);
    std::cout << str << std::endl;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen = SDL_SetVideoMode(256, 256, 32, SDL_SWSURFACE);

    if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            int alpha = (i+j) % 255;

            *((Uint32*)screen->pixels + i * 256 + j) = SDL_MapRGBA(screen->format, i, j, 255-i, alpha);
        }
    }

    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

    SDL_Flip(screen);

    SDL_Quit();

    printf("SDL!\n");
    return 0;
}
