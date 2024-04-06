// Block.cpp
#include "Block.h"

Block::Block(int x, int y, int width, int height) : active(true) {
    rect = { x, y, width, height };
}

Block::~Block() {}

void Block::moveDown() {
    rect.y += 1.5;
}

const SDL_Rect* Block::getRect() const {
    return &rect;
}



bool Block::isActive() const {
    return active;
}

void Block::setActive(bool active) {
    this->active = active;
}
