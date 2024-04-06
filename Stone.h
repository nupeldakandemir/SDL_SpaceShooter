// Stone.h
#ifndef STONE_H
#define STONE_H

#include <SDL2/SDL.h>

class Stone {
private:
    SDL_Rect rect;
    SDL_Texture* texture;

public:
    Stone(int x, int y, int w, int h, SDL_Texture* tex);
    ~Stone();
    SDL_Rect* getRect();
    SDL_Texture* getTexture();
    bool isActive();
    void moveDown();
    void setActive(bool active);
};

#endif
