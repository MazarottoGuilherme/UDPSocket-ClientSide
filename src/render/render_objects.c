#include "../render/render_objects.h"

#include "render.h"

void drawText(
    TTF_Font *font,
    const char *text,
    int x,
    int y,
    SDL_Color color
) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    if (!surface) return;

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(getRenderer(), surface);

    SDL_Rect dst = { x, y, surface->w, surface->h };

    SDL_FreeSurface(surface);
    SDL_RenderCopy(getRenderer(), texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

void draw_rect(const SDL_Rect *rect, SDL_Color color) {
    SDL_SetRenderDrawColor(getRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(getRenderer(), rect);
}

void fill_rect(const SDL_Rect *rect, SDL_Color color) {
    SDL_SetRenderDrawColor(getRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(getRenderer(), rect);
}
