#include "map_render.h"
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