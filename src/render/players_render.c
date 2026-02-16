#include "players_render.h"

#include <SDL_rect.h>
#include <SDL_render.h>

#include "render.h"
#include "render_objects.h"
#include "../net/net.h"
#include "../animation/animation.h"
Player playerPrincipal;

void render_players(int cx, int cy, TTF_Font *font) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i].active)
            continue;

        int SPRITE_SIZE = 32;
        int scale = 2;

        Frame* f = &getPlayerIdleAnimation()->frames[getPlayerIdleAnimation()->lastFrame];
        SDL_Rect srcrect = { f->offset_x + ((getPlayerIdleAnimation()->lastFrame) * 32 ), f->offset_y, f->width, f->height };


        SDL_Rect r = {
            (int)((players[i].x - cx) - (f->width * scale) / 2),
            (int)((players[i].y - cy) - (f->height * scale) / 2),
            f->width * scale,
            f->height * scale
        };

        SDL_RenderCopy(getRenderer(), getPlayerTexture(), &srcrect, &r);

        Uint32 now = SDL_GetTicks();
        if (now - getPlayerIdleAnimation()->lastTick > getPlayerIdleAnimation()->delay) {
            getPlayerIdleAnimation()->lastFrame++;
            getPlayerIdleAnimation()->lastTick = now;
            if (getPlayerIdleAnimation()->lastFrame == getPlayerIdleAnimation()->frameCount)
                getPlayerIdleAnimation()->lastFrame = 0;
        }

        if (players[i].id == user_id) {
            playerPrincipal.x = players[i].x;
            playerPrincipal.y = players[i].y;
        }

        int hitboxW = 25;
        int hitboxH = 50;

        // SDL_Rect hitbox;
        // hitbox.x = ((playerPrincipal.x - camera.x) - (hitboxW/2));   // desconta a câmera
        // hitbox.y = (playerPrincipal.y - camera.y) - (hitboxH/2);
        // hitbox.w = hitboxW;
        // hitbox.h = hitboxH;

        int tx = (players[i].x - cx - 32);
        int ty = (players[i].y - cy - 32);

        drawText(font, players[i].name, tx, ty, (SDL_Color){0,0,0,255});
    }

}