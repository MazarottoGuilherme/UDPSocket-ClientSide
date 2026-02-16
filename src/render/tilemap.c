#include "tilemap.h"

#include "render.h"

void drawTile(int tileId, int pixelX, int pixelY, Texture texture)
{
    int tileIndex = tileId - 1;
    int tilesPerRow = texture.columns;

    SDL_Rect src = {
        (tileIndex % tilesPerRow) * TILE_SIZE,
        (tileIndex / tilesPerRow) * TILE_SIZE,
        TILE_SIZE, TILE_SIZE
    };
    SDL_Rect dest = { pixelX, pixelY, TILE_SIZE, TILE_SIZE };

    SDL_RenderCopy(getRenderer(), texture.texture, &src, &dest);
    //
    // SDL_SetRenderDrawColor(getRenderer(), 255, 0, 0, 255);
    // SDL_RenderDrawRect(getRenderer(), &dest);

}