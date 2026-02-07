#ifndef UDPSOCKETCLIENT_MAP_H
#define UDPSOCKETCLIENT_MAP_H
#include <SDL_render.h>
#define TILE_SIZE 16

typedef struct {
    const char* image;
    int first_grid;
} Tileset;

typedef struct {
    int id;
    int* tiles;
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


typedef struct {
    int offset_x;
    int offset_y;
    int width;
    int height;
} Frame;

typedef struct {
    char* name;
    int frameCount;
    int lastFrame;
    Frame* frames;
    double delay;
    Uint32 lastTick;
} Animation;

typedef struct {
    int animationCount;
    Animation* animations;
} AnimationSet;

Map* load_map(const char* path);
Texture loadTexture(const char* image);
Texture loadTexture(const char* image);
AnimationSet* loadAnimations(const char* path);
Animation* getAnimation(AnimationSet* set, const char* name);
#endif //UDPSOCKETCLIENT_MAP_H