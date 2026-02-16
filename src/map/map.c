#include "map.h"
#include <stdlib.h>
#include <string.h>
#include "map_loader.h"
#include <cjson/cJSON.h>
#include "../render/render.h"

TilesetMapEntry tilesetMap[] = {
    {"../tiled/water.tsx", "/tilesets/water.png"},
    {"../tiled/hills.tsx", "/tilesets/hills.png"},
    {"collision.tsx", "/tilesets/hills.png"}
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
        cJSON* layerName = cJSON_GetObjectItem(layer, "name");

        map->layers[i].name = malloc(sizeof(char) * strlen(layerName->valuestring) + 1);
        strcpy(map->layers[i].name, layerName->valuestring);

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

void map_destroy(Map* map)
{
    if (!map) return;

    for (int i = 0; i < map->layersCount; i++) {
        free(map->layers[i].tiles);
    }

    free(map->layers);
    free(map->tilesets);
    free(map);
}