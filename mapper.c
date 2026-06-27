#define SDL_MAIN_USE_CALLBACKS 1
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

/* BG constant colors */
#define RED   0.29f
#define GREEN 0.65f
#define BLUE  1.0f
#define COLS 3
#define ROWS 2
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define IMG_W (SCREEN_WIDTH  / COLS / 4)
#define IMG_H (SCREEN_HEIGHT / ROWS / 4)

static const SDL_Color MVS_COLORS[ROWS][COLS] = {
    { {255, 220,   0, 255}, {0, 200,  80, 255}, {30, 100, 255, 255} },  /* B, C, D */
    { {220,  30,  30, 255}, {220, 220, 220, 255}, {220, 220, 220, 255} } /* A, Select, Start */
};

typedef struct {
    SDL_Window*   window;
    SDL_Renderer* renderer;
    SDL_Texture*  texture;
} AppState;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    AppState* as = (AppState*)SDL_malloc(sizeof(AppState));
    SDL_memset(as, 0, sizeof(AppState));
    *appstate = as;

    SDL_SetAppMetadata("Input Mapper", "0.1", "net.aboodmm.input-remapper");
    SDL_Log("Window BG color Red: %.2f, Green: %.2f, Blue: %.2f", 255*RED, 255*GREEN, 255*BLUE);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDL_CreateWindowAndRenderer("Input Remapper", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &as->window, &as->renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Surface* surface = IMG_Load("img/botan.png");
    if (!surface) {
        SDL_Log("IMG_Load failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    as->texture = SDL_CreateTextureFromSurface(as->renderer, surface);
    SDL_DestroySurface(surface);
    if (!as->texture) {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    AppState* as = (AppState*)appstate;

    SDL_SetRenderDrawColorFloat(as->renderer, RED, GREEN, BLUE, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(as->renderer);

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            SDL_Color c = MVS_COLORS[row][col];
            SDL_SetTextureColorMod(as->texture, c.r, c.g, c.b);

            SDL_FRect dst = {
                (float)(col * IMG_W),
                (float)(row * IMG_H),
                (float)IMG_W,
                (float)IMG_H
            };
            SDL_RenderTexture(as->renderer, as->texture, NULL, &dst);
        }
    }

    /* Reset tint so other textures aren't affected */
    SDL_SetTextureColorMod(as->texture, 255, 255, 255);

    SDL_RenderPresent(as->renderer);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    AppState* as = (AppState*)appstate;
    if (as) {
        SDL_DestroyTexture(as->texture);
        SDL_DestroyRenderer(as->renderer);
        SDL_DestroyWindow(as->window);
        SDL_free(as);
    }
    SDL_Quit();
}