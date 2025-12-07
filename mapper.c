#define SDL_MAIN_USE_CALLBACKS 1
#include <stdio.h> 
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_iostream.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

/* BG constant colors */
const float RED = 0.29f;
const float GREEN = 0.65f;
const float BLUE = 1.0f;

/*
	Initialize SDL App, create window and renderer
*/
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_SetAppMetadata("Input Mapper", "0.1", "net.aboodmm.input-remapper");
	
	SDL_Log("Window BG color Red: %.2f, Green: %.2f, Blue: %.2f", 255*RED, 255*GREEN, 255*BLUE);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Input Remapper", 640, 480, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    SDL_SetRenderDrawColorFloat(renderer, RED, GREEN, BLUE, SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/*
	Load the initial button from png file
*/
bool loadImage() {
    bool success = true;
	
	const char read_mode = 'r';

    SDL_Surface* image = IMG_LoadPNG_IO(SDL_IOFromFile("img/botan.png", &read_mode));
    if( image == NULL )
    {
        printf( "Failed %s!", SDL_GetError() );
        success = false;
    }

    return success;
}

/*
	Recolor buttons and arrange them like fightstick
*/
void transformButtons() {
	return;
}
void SDL_AppQuit(void* appstate, SDL_AppResult result) {

}
