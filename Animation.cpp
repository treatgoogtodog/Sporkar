#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include <vector>
#include "Animation.h"


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
    SDL_RenderPresent(renderer);
    SDL_RenderCopy(renderer, anim.texture, &srcRect, &destRect);
}
