
#include <SDL2/SDL_image.h>

#include "../../net/net.h"
#include "../screen.h"
#include "../../map/map.h"
#include "../../render/render.h"
#include "../../graphics/texture.h"
#include "../../render/map_render.h"
#include "../../animation/animation.h"
#include "../../config.h"
#include "./game.h"

Texture* textures;
Map* map;
SDL_Texture* playerTexture;
AnimationSet* playerSet;
Animation* playerIdle;
Camera camera;
Player playerPrincipal;

void game_init(void) {
    socket_init();
    send_login();

    map = load_map(ASSETS_DIR"/data/maps/map.json");

    textures = malloc(sizeof(Texture) * map->tilesetCount);

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i].active)
            continue;
        if (players[i].id != user_id) {
            continue;
        }
        playerPrincipal = players[i];
        playerPrincipal.x = WINDOW_WIDTH/2;
        playerPrincipal.y = WINDOW_HEIGHT/2;
    }

    for (int i = 0; i < map->tilesetCount; i++) {
        textures[i] = texture_load(map->tilesets[i].image);
    }

    SDL_Surface* playerSurface = IMG_Load(ASSETS_DIR "/tilesets/player.png");
    if (!playerSurface) {
        printf("IMG_Load Error: %s\n", IMG_GetError());
        exit(1);
    }
    playerTexture = SDL_CreateTextureFromSurface(getRenderer(), playerSurface);
    if (!playerTexture) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_FreeSurface(playerSurface);

    playerSet = loadAnimations(ASSETS_DIR "/data/animations/player.json");

    playerIdle = getAnimation(playerSet, "idle");
    playerIdle->delay = 120;
    camera.x = WINDOW_WIDTH ;
    camera.y = WINDOW_HEIGHT;
    camera.width = WINDOW_WIDTH;
    camera.height = WINDOW_HEIGHT;

}

void camera_update() {
    float playerX, playerY;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (players[i].id != user_id) {
            continue;;
        }
        playerX = players[i].x;
        playerY = players[i].y;

    }
    camera.x = playerX - camera.width / 2;
    camera.y = playerY - camera.height / 2;

    // opcional: limitar para não sair do mapa
    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    if (camera.x > map->width * TILE_SIZE - camera.width)
        camera.x = map->width * TILE_SIZE - camera.width;
    if (camera.y > map->height * TILE_SIZE - camera.height)
        camera.y = map->height * TILE_SIZE - camera.height;

}

void game_handle_event(SDL_Event *e) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        if (e->button.button == SDL_BUTTON_LEFT) {


        }
    }
}

void game_update(void) {
    int dx = 0, dy = 0;

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_W]) dy = -1;
    if (keys[SDL_SCANCODE_S]) dy =  1;
    if (keys[SDL_SCANCODE_A]) dx = -1;
    if (keys[SDL_SCANCODE_D]) dx =  1;

    if (dx || dy)
        send_input(dx, dy);

    if (net_update() <0) {
        change_screen(SCREEN_LOGIN);
    }
}

void game_render(void) {


    camera_update(playerPrincipal.x, playerPrincipal.y);
    map_render(map, textures, camera);
    SDL_Color debugColor = {255, 0, 0, 100};
    SDL_Color c;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i].active)
            continue;


        int SPRITE_SIZE = 32;
        int scale = 2;

        Frame* f = &playerIdle->frames[playerIdle->lastFrame];
        SDL_Rect srcrect = { f->offset_x + ((playerIdle->lastFrame) * 32 ), f->offset_y, f->width, f->height }; // só recorta a imagem do spritesheet, aqui nunca deve mexer, aqui nao muda a posicao na tela


        int cx = (int)players[i].x;
        int cy = (int)players[i].y;

        SDL_Rect debugRect = {
            cx ,
            cy ,
            SPRITE_SIZE * scale,
            SPRITE_SIZE * scale
        };

        SDL_Point point = {
            (debugRect.x)  + (f->offset_x * scale),
            (debugRect.y) + (f->offset_y* scale)
        };

        SDL_Rect r = {
            (int)(players[i].x - camera.x) + f->offset_x * scale,
            (int)(players[i].y - camera.y) + f->offset_y * scale,
            f->width * scale,
            f->height * scale
        };

        SDL_RenderCopy(getRenderer(), playerTexture, &srcrect, &r);

        Uint32 now = SDL_GetTicks();
        if (now - playerIdle->lastTick > playerIdle->delay) {
            playerIdle->lastFrame++;
            playerIdle->lastTick = now;
            if (playerIdle->lastFrame == playerIdle->frameCount)
                playerIdle->lastFrame = 0;
        }

        if (players[i].id == user_id) {
            playerPrincipal.x = players[i].x;
            playerPrincipal.y = players[i].y;
        }


        // if (players[i].id == user_id)
        //     c = (SDL_Color){255, 0,0,255};
        // else
        //     c = (SDL_Color){0,0,255,255};

        // fill_rect(&r, c);
    }
}

void game_shutdown(void) {
    for (int i = 0; i < map->tilesetCount; i++)
        texture_destroy(&textures[i]);

    free(textures);

    SDL_DestroyTexture(playerTexture);

    animation_set_destroy(playerSet);
    map_destroy(map);

    send_logout();
}