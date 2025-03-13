#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include <vector>


struct Frame {
    int x; // Tọa độ X trên spritesheet
    int y; // Tọa độ Y trên spritesheet
    int width;  // Chiều rộng của khung hình
    int height; // Chiều cao của khung hình
};

struct Animation {
    SDL_Texture* texture;    // Texture của spritesheet
    std::vector<Frame> frames; // Danh sách các khung hình
    int currentFrame;        // Khung hình hiện tại
    int frameTime;           // Thời gian hiển thị mỗi khung
    int elapsedTime;         // Thời gian đã trôi qua
};


SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void UpdateAnimation(Animation& anim, int deltaTime) {
    anim.elapsedTime += deltaTime;

    if (anim.elapsedTime >= anim.frameTime) {
        anim.elapsedTime = 0;
        anim.currentFrame = (anim.currentFrame + 1) % anim.frames.size();
    }
}

void DrawAnimation(SDL_Renderer* renderer, Animation& anim, int x, int y) {
    Frame frame = anim.frames[anim.currentFrame];
    SDL_Rect srcRect = { frame.x, frame.y, frame.width, frame.height };
    SDL_Rect destRect = { x, y, frame.width, frame.height };
    SDL_RenderCopy(renderer, anim.texture, &srcRect, &destRect);
}
