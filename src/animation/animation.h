#ifndef UDPSOCKETCLIENT_ANIMATION_H
#define UDPSOCKETCLIENT_ANIMATION_H
#include <SDL_stdinc.h>
#include <SDL2/SDL.h>

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

AnimationSet* loadAnimations(const char* path);
Animation* getAnimation(AnimationSet* set, const char* name);
void animation_set_destroy(AnimationSet* set);
SDL_Texture* getPlayerTexture(void);
AnimationSet* getPlayerAnimationSet(void);
Animation* getPlayerIdleAnimation(void);
#endif //UDPSOCKETCLIENT_ANIMATION_H