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
    return rect.y < 600; // Deðiþtirilebilir, burada yýldýzýn ekranýn altýna geldiðinde inaktif olmasýný kontrol ediyoruz
}

void Stone::moveDown() {
    rect.y += 2; // Yýldýzlarýn düþme hýzý, isteðe baðlý olarak deðiþtirilebilir
    if (rect.y > 600) { // Eðer yýldýz ekranýn dýþýna çýkarsa tekrar üstten baþlat
        rect.x = rand() % 800;
        rect.y = -100 - rand() % 300; // Yýldýzýn ekrandan çýktýktan sonra rastgele bir konuma baþlamasý
    }
}



void Stone::setActive(bool active) {
    if (!active) {
        rect.x = rand() % 800;
        rect.y = -100 - rand() % 300; // Yýldýzýn ekranýn üstünde yeniden baþlatýlmasý
    }
}
