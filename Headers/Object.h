
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <deque>
#include <string>
#include "MiscLoader.h"
#include "CharacterSystem.h"
#include "JsonParsers.h"


class BaseObject {
public:
    BaseObject(const std::string& texturePath, int x, int y, int width, int height, SDL_Renderer* renderer, int type);
    ~BaseObject();

    void render(SDL_Renderer* renderer) const;
    void move(int speed);

    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
	int getType() const { return type; }
    SDL_Texture* getTexture() const { return texture; };
    bool reg;

private:
    int x, y, width, height;
    SDL_Texture* texture;    
	int type;
};

class PathManager {
public:
    void addNewObject(int x, int y, int width, int height, const std::string& texturePath, SDL_Renderer* renderer, int type);

    void removeOldObjects(int playerX);

    void renderPath(SDL_Renderer* renderer) const;

    void renderGround(SDL_Renderer* renderer, SDL_Texture* texture, int offset) const;

    void UPDATE(SDL_Renderer* renderer, int speed);

    BaseObject* checkCollision(Player& player) const;

    void cleanUp();

private:
    std::deque<BaseObject*> pathObjects; 
};

class dog {
private:
    int x, y, width, height;
    SDL_Texture* texture;
	std::map<std::string, Animation> texturedata;
public:
    dog(int x, int y,int width,int height, const std::string& texturePTH, SDL_Renderer* renderer, float multipler);
    ~dog();
    void render(SDL_Renderer* renderer, const int& deltaTime, const float& multipler);
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; };
    
};