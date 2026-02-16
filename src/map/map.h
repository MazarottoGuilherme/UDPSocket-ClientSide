#ifndef UDPSOCKETCLIENT_MAP_H
#define UDPSOCKETCLIENT_MAP_H
#include <SDL2/SDL.h>
#define TILE_SIZE 16

typedef struct {
    const char* image;
    int first_grid;
} Tileset;

typedef struct {
    int id;
    int* tiles;
    char* name;
}Layer;

typedef struct {
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    // int *tiles;
    int layersCount;
    Layer* layers;
    Tileset* tilesets;
    int tilesetCount;
} Map;

typedef  struct {
    SDL_Texture* texture;
    int columns;
}Texture;

typedef struct {
    const char* source;
    const char* image;
} TilesetMapEntry;

Map* load_map(const char* path);
void map_destroy(Map* map);

#endif //UDPSOCKETCLIENT_MAP_H