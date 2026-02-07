#include "map.h"

#include <SDL_image.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "map_loader.h"
#include <cjson/cJSON.h>
#include "../render/render.h"

TilesetMapEntry tilesetMap[] = {
    {"../tiled/water.tsx", "/tilesets/water.png"},
    {"../tiled/hills.tsx", "/tilesets/hills.png"}
};

const char* getMappedTileset(const char* source) {
    for (int i = 0; i < sizeof(tilesetMap)/sizeof(tilesetMap[0]); i++) {
        if (strcmp(tilesetMap[i].source, source) == 0) {
            return tilesetMap[i].image;
        }
    }
    return NULL;
}


Map* load_map(const char* path)
{
    char* jsonText = read_file(path);
    if (!jsonText) return NULL;

    cJSON* root = cJSON_Parse(jsonText);
    free(jsonText);
    if (!root) return NULL;

    Map* map = malloc(sizeof(Map));
    if (!map) {
        cJSON_Delete(root);
        return NULL;
    }

    map->width = cJSON_GetObjectItem(root, "width")->valueint;
    map->height = cJSON_GetObjectItem(root, "height")->valueint;
    map->tileWidth = cJSON_GetObjectItem(root, "tilewidth")->valueint;
    map->tileHeight = cJSON_GetObjectItem(root, "tileheight")->valueint;

    // Layers
    cJSON* layers = cJSON_GetObjectItem(root, "layers");
    if (!layers || cJSON_GetArraySize(layers) == 0) {
        cJSON_Delete(root);
        free(map);
        return NULL;
    }

    int layersSizeCount = cJSON_GetArraySize(layers);

    map->layersCount = layersSizeCount;
    map->layers = malloc(sizeof(Layer) * layersSizeCount);
    for (int i = 0; i < layersSizeCount; i++) {
        cJSON* layer = cJSON_GetArrayItem(layers, i);
        cJSON* data = cJSON_GetObjectItem(layer, "data");
        int count = cJSON_GetArraySize(data);

        map->layers[i].tiles = malloc(sizeof(int) * count);
        for (int t = 0; t < count; t++) {
            map->layers[i].tiles[t] = cJSON_GetArrayItem(data, t)->valueint;
        }
    }

    // Tilesets
    cJSON* tsArray = cJSON_GetObjectItem(root, "tilesets");
    map->tilesetCount = cJSON_GetArraySize(tsArray);
    map->tilesets = malloc(sizeof(Tileset) * map->tilesetCount);

    for (int i = 0; i < map->tilesetCount; i++) {
        cJSON* ts = cJSON_GetArrayItem(tsArray, i);

        map->tilesets[i].first_grid = cJSON_GetObjectItem(ts, "firstgid")->valueint;
        char* source_image = cJSON_GetObjectItem(ts, "source")->valuestring;

        map->tilesets[i].image = getMappedTileset(source_image);

    }

    cJSON_Delete(root);
    return map;
}


Texture loadTexture(const char* image)
{
    char path[256];
    snprintf(path, sizeof(path), "%s%s", ASSETS_DIR, image);

    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        printf("IMG_Load Error: %s\n", IMG_GetError());
        exit(1);
    }

    int imageWidth = surface->w;
    int columnsNumber = imageWidth / TILE_SIZE;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
    if (!texture) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        exit(1);
    }
    return (Texture){texture, columnsNumber};


}

AnimationSet* loadAnimations(const char* path)
{
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* data = malloc(size + 1);
    fread(data, 1, size, f);
    data[size] = 0;
    fclose(f);

    cJSON* root = cJSON_Parse(data);
    free(data);
    if (!root) return NULL;

    int animCount = cJSON_GetArraySize(root);
    AnimationSet* set = malloc(sizeof(AnimationSet));
    set->animationCount = animCount;
    set->animations = malloc(sizeof(Animation) * animCount);

    for (int i = 0; i < animCount; i++) {
        cJSON* animObj = cJSON_GetArrayItem(root, i);
        cJSON* nameObj = cJSON_GetObjectItem(animObj, "NomeAnimacao");
        cJSON* frameCountObj = cJSON_GetObjectItem(animObj, "QtdSprites");
        cJSON* framesArr = cJSON_GetObjectItem(animObj, "frames");

        Animation* anim = &set->animations[i];
        anim->name = strdup(nameObj->valuestring);
        anim->frameCount = frameCountObj->valueint;
        anim->frames = malloc(sizeof(Frame) * anim->frameCount);

        for (int j = 0; j < anim->frameCount; j++) {
            cJSON* fObj = cJSON_GetArrayItem(framesArr, j);
            anim->frames[j].offset_x = cJSON_GetObjectItem(fObj, "offset_x")->valueint;
            anim->frames[j].offset_y = cJSON_GetObjectItem(fObj, "offset_y")->valueint;
            anim->frames[j].width    = cJSON_GetObjectItem(fObj, "width")->valueint;
            anim->frames[j].height   = cJSON_GetObjectItem(fObj, "height")->valueint;
        }
    }

    cJSON_Delete(root);
    return set;
}


Animation* getAnimation(AnimationSet* set, const char* name)
{
    for (int i = 0; i < set->animationCount; i++) {
        if (strcmp(set->animations[i].name, name) == 0)
            return &set->animations[i];
    }
    return NULL;
}