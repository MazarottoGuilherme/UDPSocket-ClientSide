#ifndef UDPSOCKETCLIENT_RENDER_H
#define UDPSOCKETCLIENT_RENDER_H
#include <SDL2/SDL.h>

void initRenderer(char* title);
void destroyRenderer(void);
SDL_Window* getWindow(void);
SDL_Renderer* getRenderer(void);

#endif //UDPSOCKETCLIENT_RENDER_H