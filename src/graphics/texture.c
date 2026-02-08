#include "texture.h"

#include <SDL2/SDL_image.h>
#include "../render/render.h"
#include "../config.h"

Texture texture_load(const char* image)
{
    char path[256];
    snprintf(path, sizeof(path), "%s%s", ASSETS_DIR, image);

    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        printf("IMG_Load Error: %s\n", IMG_GetError());
        exit(1);
    }

    int imageWidth = surface->w;
    int columnsNumber = imageWidth / TILE_SIZE;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
    if (!texture) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_FreeSurface(surface);

    return (Texture){texture, columnsNumber};
}


void texture_destroy(Texture* tex) {
    SDL_DestroyTexture(tex->texture);
}