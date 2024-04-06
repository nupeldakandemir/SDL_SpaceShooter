#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctime> // Ekledim

#include "GameManager.h"

int main(int argc, char* args[]) {
    srand(time(NULL)); // Rastgelelik için seed

    GameManager gameManager;
    gameManager.run();

    return 0;
}
