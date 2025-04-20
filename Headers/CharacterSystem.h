#pragma once
// ALL TIMER ARE SET IN MILLISECOND!!
#include <SDL.h>
#include <string>
#include "JsonParsers.h"
#include "Animation.h"
#include <map>

class Player {
public:
    Player(int x, int y, const std::string& texturePTH, const std::string& textureDAT, SDL_Renderer* renderer, const float& multipler);
    ~Player();

    void update(bool isJumping, float gravity, float JumpStreg, int groundLvl);

    void render(SDL_Renderer* renderer, const int& deltaTime, const float& multipler);

    void UpdateIDs(bool isJumping);
    int health;
    int getX() const { return x; }
    int getY() const { return y; }
    int getWid() const { return width; }
    int getHei() const { return height; }
private:
    int x, y;
    float multipler;
    int width, height;
    float VelY;
    int IDs = -1;
    std::string curr_anim = "Idle";
    SDL_Texture* texture;
    std::map<std::string, Animation> texturedata;
};