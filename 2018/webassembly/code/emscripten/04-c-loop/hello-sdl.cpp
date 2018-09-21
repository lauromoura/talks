#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

struct context {
    SDL_Window *screen;
    SDL_Renderer *renderer;
    SDL_Texture *image;
    SDL_Rect rect;
};

extern "C" {

void loop_fn(void *data)
{
    context *c = (context*)data;
    static int i = 0;

    SDL_RenderClear(c->renderer);
    SDL_RenderCopy(c->renderer, c->image, NULL, &c->rect);
    SDL_RenderPresent(c->renderer);

    i++;
    printf("Rendering frame %d\n", i);
}

int main() {
    printf("Starting SDL demo!\n");

    const int SIZE = 480;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    context ctx;


    printf("Opening screen\n");
    ctx.screen = SDL_CreateWindow("Demo", 100, 100, SIZE, SIZE, 0);
    if (!ctx.screen) {
        printf("Failed to get screen: %s\n", SDL_GetError());
        return 1;
    }

    ctx.renderer = SDL_CreateRenderer(ctx.screen, -1, SDL_RENDERER_ACCELERATED);
    if (!ctx.renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return 1;
    }
    const char* filename = "native_floripa.png";
    printf("Opening image\n");
    ctx.image = IMG_LoadTexture(ctx.renderer, filename);
    if (!ctx.image) {
        printf("Failed to get image %s: %s\n", filename, IMG_GetError());
        return 1;
    }
    int w, h;
    SDL_QueryTexture(ctx.image, NULL, NULL, &w, &h);

    ctx.rect.x = 0;
    ctx.rect.y = 0;
    ctx.rect.w = w;
    ctx.rect.h = h;

#ifdef __EMSCRIPTEN__
    int simulate_infinite_loop = 1;
    int use_requestAnimationFrame;
    emscripten_set_main_loop_arg(loop_fn, &ctx,
                                 use_requestAnimationFrame,
                                 simulate_infinite_loop);
#else

    // FIXME add regular main loop

#endif
    return 0;
}
 
}
