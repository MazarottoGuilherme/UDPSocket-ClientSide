#ifndef UDPSOCKETCLIENT_MAP_RENDER_H
#define UDPSOCKETCLIENT_MAP_RENDER_H
#include "../map/map.h"
#include "../screens/game/game.h"

Texture* getTextureForTile(Map* map, Texture* textures, int tileId);
void map_render(Map* map, Texture* textures, Camera camera);
#endif //UDPSOCKETCLIENT_MAP_RENDER_H