#ifndef UDPSOCKETCLIENT_RENDER_TEXT_H
#define UDPSOCKETCLIENT_RENDER_TEXT_H

#include <SDL2/SDL_ttf.h>

void drawText(
    TTF_Font *font,
    const char *text,
    int x,
    int y,
    SDL_Color color
);

void draw_rect(const SDL_Rect *rect, SDL_Color color);
void fill_rect(const SDL_Rect *rect, SDL_Color color);
#endif //UDPSOCKETCLIENT_RENDER_TEXT_H