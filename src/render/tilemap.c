#include "tilemap.h"

#include "render.h"

void drawTile(int tileId, int x, int y, Texture texture)
{
    int tileIndex = tileId - 1;
    int tilesPerRow = texture.columns;

    int srcX = (tileIndex % tilesPerRow) * TILE_SIZE;
    int srcY = (tileIndex / tilesPerRow) * TILE_SIZE;

    SDL_Rect src = { srcX, srcY, TILE_SIZE, TILE_SIZE };
    SDL_Rect dest = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

    SDL_RenderCopy(getRenderer(), texture.texture, &src, &dest);
}
