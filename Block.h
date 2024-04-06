#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>

class Block {
public:
    Block(int x, int y, int width, int height);
    ~Block();
    void moveDown();
    const SDL_Rect* getRect() const; 
    bool isActive() const;
    void setActive(bool active);

private:
    SDL_Rect rect;
    bool active;
};

#endif // BLOCK_H
