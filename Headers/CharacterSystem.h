#pragma once
// ALL TIMER ARE SET IN MILLISECOND!!
#include <SDL.h>
#include <string>
#include "JsonParsers.h"
#include "Animation.h"
#include "Object.h"
#include <map>

enum PLAYERSTATE {
	IDLE,
	RUNNING,
	JUMPING,
	FALLING,
	DASHING,
	LANDING
};

class player {
public:
	player(int x, int y, const std::string& texturePTH, const std::string& textureDAT, SDL_Renderer* renderer);
	~player();

	void update(bool isJumping, float gravity, float JumpStreg, int groundLvl);

	void render(SDL_Renderer* renderer, const int& deltaTime);

	BaseObject* checkCollision(int x, int y);

	void UpdateIDs(bool isJumping);

	int getX() const { return x; }
	int getY() const { return y; }
	int getWid() const { return width; }
	int getHei() const { return height; }
private:
	int x, y;
	int width, height;
	float VelY;
	int IDs = -1;
	std::string curr_anim = "Idle";
	SDL_Texture* texture;
	std::map<std::string, Animation> texturedata;
};