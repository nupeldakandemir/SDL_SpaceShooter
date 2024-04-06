// Player.h
#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class Player {
public:
    Player(int width, int height);
    ~Player();
    void moveLeft();
    void moveRight();
    SDL_Rect getRect() const;

private:
    SDL_Rect rect;
};

#endif // PLAYER_H
