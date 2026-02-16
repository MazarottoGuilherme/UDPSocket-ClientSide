#ifndef UDPSOCKETCLIENT_RENDER_TEXT_H
#define UDPSOCKETCLIENT_RENDER_TEXT_H

#include <SDL2/SDL_ttf.h>

typedef struct {
    SDL_Texture* texture;
    int w;
    int h;
} Text;

void drawText(
    TTF_Font *font,
    const char *text,
    int x,
    int y,
    SDL_Color color
);

Text createText(TTF_Font* font, const char* str, SDL_Color color );
void drawTextCached(Text* t, int x, int y);
void draw_rect(const SDL_Rect *rect, SDL_Color color);
void fill_rect(const SDL_Rect *rect, SDL_Color color);
#endif //UDPSOCKETCLIENT_RENDER_TEXT_H