#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

struct Frame {
    int x; // Tọa độ X trên spritesheet
    int y; // Tọa độ Y trên spritesheet
    int width;  // Chiều rộng của khung hình
    int height; // Chiều cao của khung hình
    Frame(int inpx, int inpy, int inpw, int inph) :x(inpx), y(inpy), width(inpw), height(inph) {}
};

struct Animation {
    SDL_Texture* texture;    // Texture của spritesheet
    std::vector<Frame> frames; // Danh sách các khung hình
    int elapsedTime = 0;
    int frameTime = 72; // 71.4ms~72 frametime => 14Fps
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

void RenderParallaxBackground(SDL_Renderer* renderer, std::vector<Layer>& layers, int screenWidth, int screenHeight);
