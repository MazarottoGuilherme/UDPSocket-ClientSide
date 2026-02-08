#include "map_render.h"
#include "tilemap.h"
#include "../config.h"

Texture* getTextureForTile(Map* map, Texture* textures, int tileId)
{
    for (int i = map->tilesetCount - 1; i >= 0; i--) {
        if (tileId >= map->tilesets[i].first_grid) {
            return &textures[i];
        }
    }
    return NULL;
}

void map_render(Map* map, Texture* textures)
{
    for (int l = 0; l < map->layersCount; l++) {
        for (int y = 0; y < HEIGHT_TILES; y++) {
            for (int x = 0; x < WIDTH_TILES; x++) {

                int tileIndex = y * map->width + x;
                int tileId = map->layers[l].tiles[tileIndex];

                if (tileId == 0)
                    continue;

                Texture* tex = getTextureForTile(map, textures, tileId);
                if (!tex)
                    continue;

                int localTileId =
                    tileId - map->tilesets[tex - textures].first_grid + 1;

                drawTile(localTileId, x, y, *tex);
            }
        }
    }
}
