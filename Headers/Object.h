
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <deque>
#include <string>
#include "CharacterSystem.h"
#include "JsonParsers.h"


enum PowerUpEffect {
	NONE,
    HYPER,
    NUKE,
    GAMBLE
};

class BaseObject;
class PowerUp;
class dog;

class PathManager {
public:
    void addNewObject(int x, int y, int width, int height, const std::string& texturePath, SDL_Renderer* renderer, int type);

    void addNewPowerUp(int x, int y, int width, int height, const std::string& texturePath, SDL_Renderer* renderer, PowerUpEffect Effect);

    void removeOldObjects(int playerX);

    void renderPath(SDL_Renderer* renderer) const;

    void renderGround(SDL_Renderer* renderer, SDL_Texture* texture, int offset) const;

    void UPDATE(SDL_Renderer* renderer, int speed);

    BaseObject* checkCollision(Player& player) const;

	PowerUp* checkPowerUpCollision(Player& player) const;

    void cleanUp();

private:
    std::deque<BaseObject*> pathObjects; 
	std::deque<PowerUp*> powerUps; // Only one powerup at a time but easier to manage along with obstacles
};

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

class PowerUp {
public:
	PowerUp(const std::string& texturePath, int x, int y, int width, int height, SDL_Renderer* renderer, PowerUpEffect Effect);
	~PowerUp();
	void render(SDL_Renderer* renderer) const;
	void move(int speed);
	int getX() const { return x; }
	int getY() const { return y; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	PowerUpEffect getEffect() const { return effect; }
	SDL_Texture* getTexture() const { return texture; }
    
    bool reg = false;
private:
	int x, y, width, height;
	SDL_Texture* texture;
	PowerUpEffect effect;
};