#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

struct Frame {
    int x; 
    int y; 
    int width;
    int height;
    Frame(int inpx, int inpy, int inpw, int inph) :x(inpx), y(inpy), width(inpw), height(inph) {}
};

struct Animation {
    SDL_Texture* texture;
    std::vector<Frame> frames;
    int elapsedTime = 0;
    int frameTime = 72;
    int currentFrame = 0;
    void addframe(Frame f) {
        frames.push_back(f);
    }
};

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& path);

void UpdateAnimation(Animation& anim, int deltaTime);

void DrawAnimation(SDL_Renderer* renderer, Animation& anim, int x, int y, float multipler);

void DrawAnimFrame(SDL_Renderer* renderer, Animation& anim, int x, int y, int frameID, float multipler);

void DrawTexture(SDL_Renderer* renderer, SDL_Texture* Texture, int x, int y, int wid, int hei);

struct Layer {
    SDL_Texture* texture;
    float speed;       
    float xOffset;     

    Layer(std::string path, float speed, float xOffset, SDL_Renderer* renderer) {
        this->speed = speed;
        this->xOffset = xOffset;
        this->texture = LoadTexture(renderer, path);
    }
};

void RenderParallaxBackground(SDL_Renderer* renderer, std::vector<Layer>& layers, int screenWidth, int screenHeight, int deltaTime, float speed);
