#include "Headers/SDL_Manager.h"
#include "Headers/Animation.h"
#include "Headers/JsonParsers.h"
#include "Headers/Object.h"
#include "Headers/CharacterSystem.h"
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
    SDL_Event event;
    bool running = true;
    uint32_t previousTime = SDL_GetTicks();
    player PLAYER;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        PLAYER.SetPosition(400, 300);
        uint32_t currentTime = SDL_GetTicks();
        int deltaTime = currentTime - previousTime;
        
        SDL_Delay(16 - deltaTime);
        if (deltaTime > 16) {
            std::cout << "Warning: Unoptimal framerate. Suspecting." << std::endl;
        }
        SDL_Rect line = { 100, 100, 600, 32 };
        SDL_SetRenderDrawColor(sdlManager.GetRenderer(), 255, 0, 0, 255);
        SDL_RenderFillRect(sdlManager.GetRenderer(), &line);
        //SDL_SetRenderDrawColor(sdlManager.GetRenderer(), 0, 0, 0, 255);
        //SDL_RenderClear(sdlManager.GetRenderer());
        //SDL_RenderPresent(sdlManager.GetRenderer());
        
        previousTime = currentTime;
    }
    return 0;
}
