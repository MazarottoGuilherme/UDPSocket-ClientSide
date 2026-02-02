//
// Created by guilherme on 2/1/26.
//

#include "render.h"
SDL_Window* window;
SDL_Renderer* renderer;

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

void initRenderer() {
    window = SDL_CreateWindow("Hello, World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Failed to create window: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

SDL_Window* getWindow() {
    return window;
}

SDL_Renderer* getRenderer() {
    return renderer;
}