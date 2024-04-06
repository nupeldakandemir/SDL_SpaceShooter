// GameManager.h
#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <chrono>
#include "Player.h"
#include "Bullet.h"
#include "Block.h"
#include "Stone.h"


class GameManager {
public:
    GameManager();
    ~GameManager();
    void run();

private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    TTF_Font* font;
    Player player;
    Bullet bullet;
    std::vector<Block> blocks;
    std::vector<Stone> stons;

    int score;
    bool gamePaused;

    std::chrono::steady_clock::time_point startTime; // Oyun baþlangýç zamaný

    void handleEvents();
    void moveEntities();
    void generateBlocks();
    void checkCollision();
    void checkGameStatus();
    void render();
    void gameOver(); // Oyunu sonlandýrma iþlevi
    void renderTimer(int remainingTime); // Zamanlayýcýyý ekranda gösterme iþlevi

    SDL_Texture* playerTexture;
    SDL_Texture* bulletTexture;
    SDL_Texture* blockTexture1;
    SDL_Texture* blockTexture2;
};

#endif // GAMEMANAGER_H
