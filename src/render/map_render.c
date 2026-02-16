#include "map_render.h"

#include "render.h"
#include "tilemap.h"

Texture* getTextureForTile(Map* map, Texture* textures, int tileId)
{
    for (int i = map->tilesetCount - 1; i >= 0; i--) {
        if (tileId >= map->tilesets[i].first_grid) {
            return &textures[i];
        }
    }
    return NULL;
}

void map_render(Map* map, Texture* textures, Camera camera)
{
    int startX = camera.x / TILE_SIZE;
    int startY = camera.y / TILE_SIZE;
    int endX   = (camera.x + camera.width) / TILE_SIZE + 1;
    int endY   = (camera.y + camera.height) / TILE_SIZE + 1;

    if (endX > map->width) endX = map->width;
    if (endY > map->height) endY = map->height;

    for (int l = 0; l < map->layersCount; l++) {
        for (int y = startY; y < endY; y++) {
            for (int x = startX; x < endX; x++) {
                int tileIndex = y * map->width + x;
                int tileId = map->layers[l].tiles[tileIndex];
                if (!tileId) continue;

                Texture* tex = getTextureForTile(map, textures, tileId);
                if (!tex) continue;

                int localTileId =
                    tileId - map->tilesets[tex - textures].first_grid + 1;

                int pixelX = (int)(x * TILE_SIZE - camera.x);
                int pixelY = (int)(y * TILE_SIZE - camera.y);

                drawTile(localTileId, pixelX, pixelY, *tex);
            }
        }
    }
}

void renderMapToCache(Map* map, Texture* textures, SDL_Texture* mapCache) {
    SDL_SetRenderTarget(getRenderer(), mapCache);
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(getRenderer());

    for (int l = 0; l < map->layersCount; l++) {
        if (strcmp(map->layers[l].name, "collision") == 0) {
            continue;
        }
        for (int y = 0; y < map->height; y++) {
            for (int x = 0; x < map->width; x++) {
                int tileIndex = y * map->width + x;
                int tileId = map->layers[l].tiles[tileIndex];
                if (!tileId) continue;

                Texture* tex = getTextureForTile(map, textures, tileId);
                if (!tex) continue;

                int localTileId =
                    tileId - map->tilesets[tex - textures].first_grid + 1;

                drawTile(localTileId, x * TILE_SIZE, y * TILE_SIZE, *tex);
            }
        }
    }

    SDL_SetRenderTarget(getRenderer(), NULL);
}
