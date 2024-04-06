// Bullet.cpp
#include "Bullet.h"


// Bullet.cpp dosyasýnda
Bullet::Bullet(int x, int y, int width, int height) : active(true), rect({ x, y, width, height }) {}


Bullet::~Bullet() {}

void Bullet::moveUp() {
    rect.y -= 10;
}

const SDL_Rect* Bullet::getRect() const {
    return &rect;
}


bool Bullet::isActive() const {
    return active;
}

void Bullet::setActive(bool active) {
    this->active = active;
}
