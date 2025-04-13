#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <deque>
#include <string>

class BaseObject {
public:
    BaseObject(const std::string& texturePath, int x, int y, int width, int height, SDL_Renderer* renderer);
    ~BaseObject();
    bool checkCollision(int playerX, int playerY, int playerWidth, int playerHeight) const;

    void render(SDL_Renderer* renderer) const;

    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int x, y, width, height; 
    SDL_Texture* texture;    
};

class PathManager {
public:
    void addNewObject(int x, int y, int width, int height, const std::string& texturePath, SDL_Renderer* renderer);

    void removeOldObjects(int playerX);

    void updatePath(int playerX, int playerWidth, SDL_Renderer* renderer);

    void renderPath(SDL_Renderer* renderer) const;

    void cleanUp();

private:
    std::deque<BaseObject*> pathObjects; 
};