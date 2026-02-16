#include "../render/render.h"

SDL_Window* window;
SDL_Renderer* renderer;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initRenderer(char* title) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN| SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        printf("Failed to create window: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void destroyRenderer(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_Window* getWindow(void) {
    return window;
}

SDL_Renderer* getRenderer(void) {
    return renderer;
}

WindowSize GetWindowSize(void) {
    int w, h;
    SDL_GetWindowSize(getWindow(), &w, &h);

    WindowSize size = (WindowSize){w, h};
    return size;
}
