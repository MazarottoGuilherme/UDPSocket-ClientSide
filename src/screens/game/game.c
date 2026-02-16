
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

#include "../../render/render_objects.h"
#include "../../render/players_render.h"

Texture* textures;
Map* map;
Camera camera;
SDL_Texture* mapCache;
TTF_Font *font;
Text text;
int mapChanged = 0;

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


    camera.x = WINDOW_WIDTH ;
    camera.y = WINDOW_HEIGHT;

    camera.width = WINDOW_WIDTH;
    camera.height = WINDOW_HEIGHT;

    mapCache = SDL_CreateTexture(
        getRenderer(),
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        map->width * TILE_SIZE,
        map->height * TILE_SIZE
        );
    renderMapToCache(map, textures, mapCache);

    font = TTF_OpenFont(ASSETS_DIR "/DejaVuSans-BoldOblique.ttf", 10);
    if (!font) {
        printf("Font error: %s\n", TTF_GetError());
        exit(1);
    }

    text = createText(font, "guilherme", (SDL_Color){0,0,0,255});

}

void camera_update() {
    // WindowSize size = GetWindowSize();
    // camera.width = size.w;
    // camera.height = size.h;

    float playerX, playerY;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (players[i].active != 1 || players[i].id != user_id) {
            continue;;
        }
        playerX = players[i].x;
        playerY = players[i].y;

    }
    camera.x = playerX - camera.width / 2;
    camera.y = playerY - camera.height / 2;

    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    if (camera.x > map->width * TILE_SIZE - camera.width)
        camera.x = map->width * TILE_SIZE - camera.width;
    if (camera.y > map->height * TILE_SIZE - camera.height)
        camera.y = map->height * TILE_SIZE - camera.height;
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
    camera_update(playerPrincipal.x, playerPrincipal.y);
    // map_render(map, textures, camera);

    if (mapChanged) {
        renderMapToCache(map, textures, mapCache);
        mapChanged = 0;
    }

    SDL_Rect src = { camera.x, camera.y, camera.width, camera.height };
    SDL_Rect dst = { 0, 0, camera.width, camera.height };
    SDL_RenderCopy(getRenderer(), mapCache, &src, &dst);

    render_players(camera.x, camera.y, font);
}

void game_shutdown(void) {
    for (int i = 0; i < map->tilesetCount; i++)
        texture_destroy(&textures[i]);

    free(textures);

    SDL_DestroyTexture(getPlayerTexture());

    animation_set_destroy(getPlayerAnimationSet());
    map_destroy(map);

    send_logout();
}