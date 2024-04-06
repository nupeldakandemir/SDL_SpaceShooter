#include "GameManager.h"
#include <iostream>
#include <ctime> // srand için
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Block.h"
#include "Stone.h" // Star yerine Stone olmalý

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BLOCK_SIZE = 50;
const int MAX_BLOCKS_PER_COLUMN = 18;
const int BLOCK_GENERATION_CHANCE = 10000;
const int FONT_SIZE = 15;

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
TTF_Font* font;
std::vector<Block> blocks;
std::vector<Stone> stones; // stars vektörü stones olarak deðiþtirildi
int score;
bool gamePaused;
SDL_Texture* playerTexture;
SDL_Texture* bulletTexture;
SDL_Texture* blockTexture1;
SDL_Texture* blockTexture2;

GameManager::GameManager() : gWindow(nullptr), gRenderer(nullptr), font(nullptr),
player(70, 100), bullet(0, 0, 30, 40), score(0), gamePaused(false),
playerTexture(nullptr), bulletTexture(nullptr), blockTexture1(nullptr), blockTexture2(nullptr) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    gWindow = SDL_CreateWindow("SDL Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    font = TTF_OpenFont("arial.ttf", FONT_SIZE);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    // Load block textures
    SDL_Surface* playerSurface = SDL_LoadBMP("player.bmp");
    if (playerSurface == NULL) {
        printf("Failed to load player texture! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }
    playerTexture = SDL_CreateTextureFromSurface(gRenderer, playerSurface);
    SDL_FreeSurface(playerSurface);
    if (playerTexture == NULL) {
        printf("Failed to create texture from player surface! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Surface* bulletSurface = SDL_LoadBMP("mermi.bmp");
    if (bulletSurface == NULL) {
        printf("Failed to load bullet texture! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }
    bulletTexture = SDL_CreateTextureFromSurface(gRenderer, bulletSurface);
    SDL_FreeSurface(bulletSurface);
    if (bulletTexture == NULL) {
        printf("Failed to create texture from bullet surface! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Surface* blockSurface1 = SDL_LoadBMP("stone1.bmp");
    if (blockSurface1 == NULL) {
        printf("Failed to load block texture 1! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }
    blockTexture1 = SDL_CreateTextureFromSurface(gRenderer, blockSurface1);
    SDL_FreeSurface(blockSurface1);
    if (blockTexture1 == NULL) {
        printf("Failed to create texture from block surface 1! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Surface* blockSurface2 = SDL_LoadBMP("stone2.bmp");
    if (blockSurface2 == NULL) {
        printf("Failed to load block texture 2! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }
    blockTexture2 = SDL_CreateTextureFromSurface(gRenderer, blockSurface2);
    SDL_FreeSurface(blockSurface2);
    if (blockTexture2 == NULL) {
        printf("Failed to create texture from block surface 2! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    srand(time(0)); // Rastgele konumlar için seed oluþtur
}



GameManager::~GameManager() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

void GameManager::run() {
    while (true) {
        handleEvents();
        if (!gamePaused) {
            moveEntities();
            generateBlocks();
            checkCollision();
        }
        render();
        SDL_Delay(10);
    }
}

void GameManager::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            exit(0);
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_SPACE:
                if (!gamePaused && !bullet.isActive()) {
                    bullet = Bullet(player.getRect().x + player.getRect().w / 2 - 15, player.getRect().y, 30, 40);
                    bullet.setActive(true);
                }
                break;
            case SDLK_LEFT:
                if (!gamePaused && player.getRect().x > 0) {
                    player.moveLeft();
                }
                break;
            case SDLK_RIGHT:
                if (!gamePaused && player.getRect().x < SCREEN_WIDTH - player.getRect().w) {
                    player.moveRight();
                }
                break;
            case SDLK_x:
                exit(0);
                break;
            case SDLK_p:
                gamePaused = !gamePaused;
                break;
            }
        }
    }
}
void GameManager::moveEntities() {
    // Bullet'ýn hareketini kontrol et
    if (bullet.isActive()) {
        bullet.moveUp();
        if (bullet.getRect()->y <= 0) {
            bullet.setActive(false);
        }
    }

    // Blocks'larýn hareketini kontrol et
    for (auto& block : blocks) {
        block.moveDown();
    }

    // Stones'larýn hareketini kontrol et
    for (auto& stone : stones) { // stars yerine stones olarak deðiþtirildi
        stone.moveDown();
    }
}

void GameManager::generateBlocks() {
    if (rand() % BLOCK_GENERATION_CHANCE == 0) {
        int column = rand() % (SCREEN_WIDTH / BLOCK_SIZE);
        int y = 0;
        while (y < MAX_BLOCKS_PER_COLUMN && blocks[y].isActive()) {
            ++y;
        }
        if (y < MAX_BLOCKS_PER_COLUMN) {
            blocks.push_back(Block(column * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
        }
    }

    // Stones'larý oluþtur
    int stoneType = rand() % 100; // starType -> stoneType olarak deðiþtirildi

    if (stoneType == 5) {
        stones.push_back(Stone(rand() % 800, -100 - rand() % 300, 30, 30, blockTexture1));
    }
    else if (stoneType == 8) {
        stones.push_back(Stone(rand() % 800, -100 - rand() % 300, 50, 30, blockTexture2));
    }
}


void GameManager::checkCollision() {
    // Bullet'ýn yýldýzlarla çarpýþmasýný kontrol et
    for (auto& stone : stones) { // stars yerine stones olarak deðiþtirildi
        if (bullet.isActive() && SDL_HasIntersection(bullet.getRect(), stone.getRect())) {
            bullet.setActive(false);
            stone.setActive(false); // Yýldýzý etkisiz hale getir
            if (stone.getTexture() == blockTexture2) { // Eðer vurulan yýldýz star2 ise
                score += 20; // Skoru 20 arttýr
            }
            else {
                score += 10; // Diðer yýldýzlar için skoru 10 arttýr
            }
        }
    }

    // Bullet'ýn bloklarla çarpýþmasýný kontrol et
    for (auto& block : blocks) {
        if (bullet.isActive() && SDL_HasIntersection(bullet.getRect(), block.getRect())) {
            bullet.setActive(false);
            block.setActive(false); // Bloðu etkisiz hale getir
            score += 20; // Skoru arttýr
        }
    }
}
void GameManager::render() {

    SDL_SetRenderDrawColor(gRenderer, 30, 144, 255, 255); // Uzay mavisi rengi
    SDL_RenderClear(gRenderer);

    // Render player
    SDL_Rect playerRect = player.getRect();
    SDL_RenderCopy(gRenderer, playerTexture, NULL, &playerRect);

    // Render bullet
    if (bullet.isActive()) {
        const SDL_Rect* bulletRect = bullet.getRect();
        SDL_RenderCopy(gRenderer, bulletTexture, NULL, bulletRect);
    }

    // Render blocks
    for (auto& block : blocks) {
        if (block.isActive()) {
            const SDL_Rect* blockRect = block.getRect();
            SDL_RenderCopy(gRenderer, blockTexture1, NULL, blockRect);
        }
    }

    // Render stones
    for (auto& stone : stones) { // stars yerine stones olarak deðiþtirildi
        SDL_Rect stoneRect = *(stone.getRect());
        SDL_RenderCopy(gRenderer, stone.getTexture(), NULL, &stoneRect);
    }

    // Render score
    SDL_Color textColor = { 255, 255, 255, 255 };
    char scoreText[50];
    std::sprintf(scoreText, "Score: %d", score);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_Rect scoreRect = { SCREEN_WIDTH - 100, 20, 100, 20 };
    SDL_RenderCopy(gRenderer, scoreTexture, NULL, &scoreRect);
    SDL_DestroyTexture(scoreTexture);

    // Render instructions
    SDL_Surface* instructionSurface = TTF_RenderText_Solid(font, "Press x to exit, press p to pause", textColor);
    SDL_Texture* instructionTexture = SDL_CreateTextureFromSurface(gRenderer, instructionSurface);
    SDL_FreeSurface(instructionSurface);
    SDL_Rect instructionRect = { SCREEN_WIDTH - 200, SCREEN_HEIGHT - 30, 200, 20 };
    SDL_RenderCopy(gRenderer, instructionTexture, NULL, &instructionRect);
    SDL_DestroyTexture(instructionTexture);

    SDL_RenderPresent(gRenderer);
}
