#include "Object.h"


BaseObject::BaseObject(const std::string& texturePath, int x, int y, int width, int height, SDL_Renderer* renderer,int type) {
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
	this->type = type;
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

void PathManager::addNewObject(int x, int y, int width, int height, const std::string& texturePath, SDL_Renderer* renderer, int type) {
    BaseObject* toCreate = new BaseObject(texturePath, x, y, width, height, renderer, type);
    if (!toCreate->getTexture()) { SDL_Log("Invalid texture! Aborting Creation"); return; }
    pathObjects.push_front(toCreate);
}

void PathManager::addNewPowerUp(int x, int y, int width, int height, const std::string& texturePath, SDL_Renderer* renderer, PowerUpEffect Effect) {
    PowerUp* toCreate = new PowerUp(texturePath, x, y, width, height, renderer, Effect);
    if (!toCreate->getTexture()) { SDL_Log("Invalid texture! Aborting Creation"); return; }
    powerUps.push_front(toCreate);
}

void PathManager::removeOldObjects(int playerX) {
    while (!pathObjects.empty() && pathObjects.back()->getX() + pathObjects.back()->getWidth() < 0) {
        delete pathObjects.back();
        pathObjects.pop_back();
    }
	while (!powerUps.empty() && powerUps.back()->getX() + powerUps.back()->getWidth() < 0) {
		delete powerUps.back();
		powerUps.pop_back();
	}
}

void PathManager::UPDATE(SDL_Renderer* renderer, int speed) {
    for (BaseObject* obj : pathObjects) {
        obj->move(speed);
        if (obj->getType() == 0) {
            obj->move(speed / 2);
        }
    }
	for (PowerUp* pwd : powerUps) {
		pwd->move(speed);
	}
}

void PathManager::renderPath(SDL_Renderer* renderer) const {
    for (const BaseObject* obj : pathObjects) {
        obj->render(renderer);
    }
    for (const PowerUp* pwd : powerUps) {
        pwd->render(renderer);
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

PowerUp* PathManager::checkPowerUpCollision(Player& player) const {
	for (PowerUp* pwd : powerUps) {
		SDL_Rect PlayerHITBOX = { player.getX(), player.getY(), player.getWid(), player.getHei() };
		SDL_Rect ObjHITBOX = { pwd->getX(), pwd->getY(), pwd->getWidth(), pwd->getHeight() };
		if (SDL_HasIntersection(&PlayerHITBOX, &ObjHITBOX)) {
			return pwd;
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

PowerUp::PowerUp(const std::string& texturePTH, int x, int y, int width, int height, SDL_Renderer* renderer, PowerUpEffect Effect)
	: x(x), y(y), width(width), height(height), texture(nullptr), effect(Effect) {
	SDL_Surface* surface = IMG_Load(texturePTH.c_str());
	if (!surface) {
		SDL_Log("Failed to load texture: %s", IMG_GetError());
		return;
	}
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

PowerUp::~PowerUp() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void PowerUp::render(SDL_Renderer* renderer) const {
	SDL_Rect destRect = { x, y, width, height };
    if (this->reg) { return; }
	if (texture) {
		SDL_RenderCopy(renderer, texture, nullptr, &destRect);
	}
}

void PowerUp::move(int speed) {
	this->x -= speed;
}
