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
    bool running;
    int angle;
};

extern "C" {

static inline bool key_up(SDL_Event e, SDL_Keycode key)
{
    return e.type == SDL_KEYUP && e.key.keysym.sym == key;
}

void cleanup(context ctx)
{
    SDL_DestroyTexture(ctx.image);
    SDL_DestroyRenderer(ctx.renderer);
    SDL_DestroyWindow(ctx.screen);
    SDL_Quit();
}

void loop_fn(void *data)
{
    context *c = (context*)data;
    static int i = 0;

    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (key_up(e, SDLK_ESCAPE)) {
            printf("Exiting loop...\n");
            c->running = false;
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
            cleanup(*c);
#endif
            return;
        }

        if (key_up(e, SDLK_LEFT))
            c->angle -= 15;
        else if (key_up(e, SDLK_RIGHT))
            c->angle += 15;
    }


    SDL_RenderClear(c->renderer);
    SDL_RenderCopyEx(c->renderer, c->image, NULL, &c->rect, c->angle, 0, SDL_FLIP_NONE);
    SDL_RenderPresent(c->renderer);

    i++;
    printf("Rendering frame %d\n", i);
}

int main() {
    printf("Starting SDL demo!\n");

    const int SIZE = 470;
    const char* filename = "native_floripa.png";
    int w, h;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    context ctx;
    ctx.running = true;
    ctx.angle = 0;


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

    printf("Opening image\n");
    ctx.image = IMG_LoadTexture(ctx.renderer, filename);
    if (!ctx.image) {
        printf("Failed to get image %s: %s\n", filename, IMG_GetError());
        return 1;
    }

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
    while (ctx.running) {
        loop_fn(&ctx);

        SDL_Delay(1000/60);
    }

    cleanup(ctx);

#endif
    return 0;
}
 
}
