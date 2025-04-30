#include "Object.h"


BaseObject::BaseObject(const std::string& texturePath, int x, int y, int width, int height, SDL_Renderer* renderer) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->reg = false;
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

void BaseObject::render(SDL_Renderer* renderer) const {
    SDL_Rect destRect = { x, y, width, height };
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    }
}

void BaseObject::move(int speed) {
    this->x -= speed;
}

void PathManager::addNewObject(int x, int y, int width, int height, const std::string& texturePath, SDL_Renderer* renderer) {
    BaseObject* toCreate = new BaseObject(texturePath, x, y, width, height, renderer);
    if (!toCreate->getTexture()) { SDL_Log("Invalid texture! Aborting Creation"); return; }
    pathObjects.push_front(toCreate);
}

void PathManager::removeOldObjects(int playerX) {
    while (!pathObjects.empty() && pathObjects.back()->getX() + pathObjects.back()->getWidth() < 0) {
        delete pathObjects.back();
        pathObjects.pop_back();
    }
}

void PathManager::UPDATE(SDL_Renderer* renderer, int speed) {
    for (BaseObject* obj : pathObjects) {
        obj->move(speed);
    }
}

void PathManager::renderPath(SDL_Renderer* renderer) const {
    for (const BaseObject* obj : pathObjects) {
        obj->render(renderer);
    }
}

void PathManager::renderGround(SDL_Renderer* renderer, SDL_Texture* texture, int offset) const {
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);

    SDL_Rect destRect = { 0, 300, 800, 100 }; 
    int realOffset = offset % (textureWidth-destRect.w);
    SDL_Rect srcRect = { realOffset, 0, destRect.w, destRect.h };

    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);

    if (realOffset + destRect.w > textureWidth) {
        int remainingWidth = (realOffset + destRect.w) - textureWidth;
        SDL_Rect srcRect2 = { 0, 0, remainingWidth, destRect.h };
        SDL_Rect destRect2 = { destRect.w - remainingWidth, destRect.y, remainingWidth, destRect.h };
        SDL_RenderCopy(renderer, texture, &srcRect2, &destRect2);
    }
}

BaseObject* PathManager::checkCollision(Player& player) const {
    for (BaseObject* obj : pathObjects) {
        SDL_Rect PlayerHITBOX = { player.getX(), player.getY(), player.getWid(), player.getHei() };
        SDL_Rect ObjHITBOX = { obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight() };
        if (SDL_HasIntersection(&PlayerHITBOX, &ObjHITBOX)) {
            return obj;
        }
    }
	return nullptr;
}

void PathManager::cleanUp() {
    for (BaseObject* obj : pathObjects) {
        delete obj;
    }
    pathObjects.clear();
}

dog::dog(int x, int y, int width, int height, const std::string& texturePTH, SDL_Renderer* renderer, float multipler) 
       : x(x), y(y), width(width), height(height), texture(nullptr) { 
       SDL_Surface* surface = IMG_Load(texturePTH.c_str());
       if (!surface) {
           SDL_Log("Failed to load texture: %s", IMG_GetError());
           return;
       }
       this->texturedata = SheetReader(DOGDOGSHEETDATA, DOGDOGSPITEPATH, renderer, this->texture);
       SDL_FreeSurface(surface);
}

dog::~dog() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void dog::render(SDL_Renderer* renderer, const int& deltaTime, const float& multipler) {
    UpdateAnimation(this->texturedata["Drive"], deltaTime);
    float multi = this->getWidth() / this->texturedata["Drive"].frames.at(texturedata["Drive"].currentFrame).width;
	DrawAnimation(renderer, this->texturedata["Drive"], this->x, this->y, multi);
}