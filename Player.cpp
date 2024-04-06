// Player.cpp
#include "Player.h"

Player::Player(int width, int height) {
    rect = { 400 - width / 2, 500, width, height };
}

Player::~Player() {}

void Player::moveLeft() {
    rect.x -= 10;
}

void Player::moveRight() {
    rect.x += 10;
}

SDL_Rect Player::getRect() const {
    return rect;
}
