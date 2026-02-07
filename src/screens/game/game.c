#include "game.h"
#include "../../net/net.h"
#include "../../render/render_objects.h"
#include "../screen.h"
#include "../../map/map.h"
#include "../../render/render.h"
#include "../../render/tilemap.h"

Texture* textures;
Map* map;
SDL_Texture* playerTexture;
AnimationSet* playerSet;
Animation* playerIdle;

Texture* getTextureForTile(int tileId) {
    for (int i = map->tilesetCount - 1; i >= 0; i--) {
        if (tileId >= map->tilesets[i].first_grid) {
            return &textures[i];
        }
    }
    return NULL;
}

void game_init(void) {
    socket_init();
    send_login();

    map = load_map(ASSETS_DIR"/data/maps/map.json");

    textures = malloc(sizeof(Texture) * map->tilesetCount);

    for (int i = 0; i < map->tilesetCount; i++) {
        textures[i] = loadTexture(map->tilesets[i].image);
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

    playerSet = loadAnimations(ASSETS_DIR "/data/animations/player.json");

    playerIdle = getAnimation(playerSet, "idle");
    playerIdle->delay = 100;

}

void game_handle_event(SDL_Event *e) {

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

    for (int l = 0; l < map->layersCount; l++) {
        for (int y = 0; y < HEIGHT_TILES; y++) {
            for (int x = 0; x < WIDTH_TILES; x++) {
                int tileIndex = y * map->width + x;
                int tileId = map->layers[l].tiles[tileIndex];

                if (tileId == 0) continue;

                Texture* tex = getTextureForTile(tileId);
                if (!tex) continue;

                int localTileId = tileId - map->tilesets[tex - textures].first_grid + 1;

                drawTile(localTileId, x, y, *tex);

            }
        }
    }


    SDL_Color c;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i].active)
            continue;
        if (players[i].id != user_id) {
            continue;
        }



        Frame* f = &playerIdle->frames[playerIdle->lastFrame];
        SDL_Rect srcrect = { f->offset_x + ((playerIdle->lastFrame) * 32 ), f->offset_y, f->width, f->height };

        SDL_Rect r = { (int)players[i].x, (int)players[i].y, f->width * 2, f->height * 2 };

        SDL_RenderCopy(getRenderer(), playerTexture, &srcrect, &r);

        Uint32 now = SDL_GetTicks();
        if (now - playerIdle->lastTick > playerIdle->delay) {
            playerIdle->lastFrame++;
            playerIdle->lastTick = now;
            if (playerIdle->lastFrame == playerIdle->frameCount)
                playerIdle->lastFrame = 0;
        }

        //
        // if (players[i].id == user_id)
        //     c = (SDL_Color){255, 0,0,255};
        // else
        //     c = (SDL_Color){0,0,255,255};

        // fill_rect(&r, c);
    }
}

void game_shutdown(void) {

}