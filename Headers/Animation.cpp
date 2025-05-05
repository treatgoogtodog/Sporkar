#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include <vector>
#include "Animation.h"

using namespace std;

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

void DrawAnimation(SDL_Renderer* renderer, Animation& anim, int x, int y, float multipler) {
    Frame frame = anim.frames[anim.currentFrame];
    SDL_Rect srcRect = { frame.x, frame.y, frame.width, frame.height };
    SDL_Rect destRect = { x, y, static_cast<int>(frame.width * multipler), static_cast<int>(frame.height * multipler) };
    SDL_RenderCopy(renderer, anim.texture, &srcRect, &destRect);
}

void DrawAniationFixed(SDL_Renderer* renderer, Animation& anim, int x, int y, int wid, int hei) {
    Frame frame = anim.frames[anim.currentFrame];
    SDL_Rect srcRect = { frame.x, frame.y, frame.width, frame.height };
    SDL_Rect destRect = { x,y,wid,hei };
    SDL_RenderCopy(renderer, anim.texture, &srcRect, &destRect);
}

void DrawAnimFrame(SDL_Renderer* renderer, Animation& anim, int x, int y, int frameID, float multipler) {
    Frame frame = anim.frames[frameID];
    SDL_Rect srcRect = { frame.x, frame.y, frame.width, frame.height };
    SDL_Rect destRect = { x, y, static_cast<int>(frame.width*multipler), static_cast<int>(frame.height*multipler) };
    SDL_RenderCopy(renderer, anim.texture, &srcRect, &destRect);
}

void DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int wid, int hei) {
    SDL_Rect destRect = { x,y, wid, hei};
    SDL_RenderCopy(renderer, texture, NULL, &destRect );
}

void RenderParallaxBackground(SDL_Renderer* renderer, std::vector<Layer>& layers, int screenWidth, int screenHeight, int deltaTime, float speed) {
    for (auto& layer : layers) {
        
        float delta = static_cast<float>(deltaTime)/100;
        layer.xOffset -= layer.speed * speed * delta;

        if (layer.xOffset <= -screenWidth) {
            layer.xOffset += screenWidth;
        }

        SDL_Rect srcRect = { 0, 0, screenWidth, screenHeight };
        SDL_Rect destRect1 = { static_cast<int>(layer.xOffset), 0, screenWidth, screenHeight };
        SDL_Rect destRect2 = { static_cast<int>(layer.xOffset) + screenWidth, 0, screenWidth, screenHeight };

        SDL_RenderCopy(renderer, layer.texture, &srcRect, &destRect1);
        SDL_RenderCopy(renderer, layer.texture, &srcRect, &destRect2);
    }
}
