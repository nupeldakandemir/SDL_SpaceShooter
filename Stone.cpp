// Stone.cpp
#include "Stone.h"

Stone::Stone(int x, int y, int w, int h, SDL_Texture* tex) : texture(tex) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

Stone::~Stone() {}

SDL_Rect* Stone::getRect() {
    return &rect;
}

SDL_Texture* Stone::getTexture() {
    return texture;
}

bool Stone::isActive() {
    return rect.y < 600; // De�i�tirilebilir, burada y�ld�z�n ekran�n alt�na geldi�inde inaktif olmas�n� kontrol ediyoruz
}

void Stone::moveDown() {
    rect.y += 2; // Y�ld�zlar�n d��me h�z�, iste�e ba�l� olarak de�i�tirilebilir
    if (rect.y > 600) { // E�er y�ld�z ekran�n d���na ��karsa tekrar �stten ba�lat
        rect.x = rand() % 800;
        rect.y = -100 - rand() % 300; // Y�ld�z�n ekrandan ��kt�ktan sonra rastgele bir konuma ba�lamas�
    }
}



void Stone::setActive(bool active) {
    if (!active) {
        rect.x = rand() % 800;
        rect.y = -100 - rand() % 300; // Y�ld�z�n ekran�n �st�nde yeniden ba�lat�lmas�
    }
}
