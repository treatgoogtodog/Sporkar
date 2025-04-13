#include "Object.h"

BaseObject::BaseObject(const std::string& texturePath, int x, int y, int width, int height, SDL_Renderer* renderer) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    if (!surface) {
        SDL_Log("Failed to load texture: %s", IMG_GetError());
        texture = nullptr;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

BaseObject::~BaseObject() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

bool BaseObject::checkCollision(int playerX, int playerY, int playerWidth, int playerHeight) const {
    return x < playerX + playerWidth &&
        x + width > playerX &&
        y < playerY + playerHeight &&
        y + height > playerY;
}

void BaseObject::render(SDL_Renderer* renderer) const {
    SDL_Rect destRect = { x, y, width, height };
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    }
}

void PathManager::addNewObject(int x, int y, int width, int height, const std::string& texturePath, SDL_Renderer* renderer) {
    pathObjects.push_front(new BaseObject(texturePath, x, y, width, height, renderer));
}

void PathManager::removeOldObjects(int playerX) {
    while (!pathObjects.empty() && pathObjects.back()->getX() + pathObjects.back()->getWidth() < 0) {
        delete pathObjects.back();
        pathObjects.pop_back();
    }
}

void PathManager::updatePath(int playerX, int playerWidth, SDL_Renderer* renderer) {
    if (pathObjects.empty() || pathObjects.front()->getX() > playerX + playerWidth + 300) {
        addNewObject(pathObjects.front()->getX() - 100, 400, 100, 50, "texture.png", renderer);
    }
    removeOldObjects(playerX);
}

void PathManager::renderPath(SDL_Renderer* renderer) const {
    for (const BaseObject* obj : pathObjects) {
        obj->render(renderer);
    }
}

void PathManager::cleanUp() {
    for (BaseObject* obj : pathObjects) {
        delete obj;
    }
    pathObjects.clear();
}