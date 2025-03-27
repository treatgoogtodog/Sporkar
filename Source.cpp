#include "SDL_Manager.h"
#include "Animation.h"
#include "JsonParsers.h"
#include <iostream>
#include <string>
#include <map>

int main(int argc, char* argv[]) {
    SDL_Manager sdlManager("Wannabe gamaer", 800, 600);

    if (!sdlManager.IsInitialized()) {
        std::cout << "Unable to initialize SDL2\nErr:" << SDL_GetError();
        return 0;
    }
    SDL_Texture* texture;
    std::map <std::string, Animation> anim = SheetReader("Texture/PlayerTexture.json", "Sprite/BlackinMan.png", sdlManager.GetRenderer(), texture);
    SDL_Event event;
    bool running = true;
    uint32_t previousTime = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        uint32_t currentTime = SDL_GetTicks();
        int deltaTime = currentTime - previousTime;
        UpdateAnimation(anim["Idle"], deltaTime);
        DrawAnimation(sdlManager.GetRenderer(), anim["Idle"], 400, 300);
        
        if (sdlManager.IsKeyDown(SDL_SCANCODE_W)) {
            std::cout << "Key 'W' is being held down!" << std::endl;
        }

        if (sdlManager.IsKeyDown(SDL_SCANCODE_ESCAPE)) {
            std::cout << "Escape key pressed. Exiting!" << std::endl;
            running = false;
        }
        SDL_Delay(16);
        //SDL_SetRenderDrawColor(sdlManager.GetRenderer(), 0, 0, 0, 255);
        //SDL_RenderClear(sdlManager.GetRenderer());
        //SDL_RenderPresent(sdlManager.GetRenderer());
        
        previousTime = currentTime;
    }
    return 0;
}
