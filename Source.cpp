#include "Headers/SDL_Manager.h"
#include "Headers/Animation.h"
#include "Headers/JsonParsers.h"
#include "Headers/Object.h"
#include "Headers/CharacterSystem.h"
#include "Headers/LogicAndMechanic.h"
#include <iostream>
#include <string>
#include <map>

int main(int argc, char* argv[]) {
    SDL_Manager sdlManager("NegaRun", 800, 600);

    if (!sdlManager.IsInitialized()) {
        std::cout << "Unable to initialize SDL2\nErr:" << SDL_GetError();
        return 0;
    }

    Player* PLAYER = nullptr;
    PathManager* PATH = new PathManager();
    SDL_Event event;
  
    gameLoad(&sdlManager, PLAYER);
    gameLoop(&sdlManager, PLAYER, PATH, &event);

    // Clean up
    delete PLAYER;
    delete PATH;

    return 0;
}