// Bullet.h
#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

class Bullet {
public:
    Bullet(int x, int y, int width, int height);
    ~Bullet();
    void moveUp();
    const SDL_Rect* getRect() const;
    bool isActive() const;
    void setActive(bool active);

private:
    SDL_Rect rect;
    bool active;
};

#endif // BULLET_H
