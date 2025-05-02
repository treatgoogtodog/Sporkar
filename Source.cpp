#include "Headers/SDL_Manager.h"
#include "Headers/Animation.h"
#include "Headers/JsonParsers.h"
#include "Headers/Object.h"
#include "Headers/CharacterSystem.h"
#include "Headers/LogicAndMechanic.h"
#include "Headers/SoundAndMusic.h"  
#include <iostream>
#include <string>
#include <map>

int main(int argc, char* argv[]) {
	SDL_Manager* SDL = new SDL_Manager("NegaRun", 800, 600);

    if (!SDL->IsInitialized()) {
        std::cout << "Unable to initialize SDL2\nErr:" << SDL_GetError();
        return 0;
    }
	SoundManager* SFX =new SoundManager();
    dog* DOG = new dog(50, 300, 100, 100, DOGDOGSPITEPATH, SDL->GetRenderer(), 0.3f);
	Player* PLAYER = new Player(250, 300, PLAYERSPRITEPATH, PLAYERSPRITESHEETDATA, SDL->GetRenderer(), 1.2f);
	TextHandler* TEXT = new TextHandler(SDL->GetRenderer());
    PathManager* PATH = new PathManager();
    SDL_Event event;
    std::vector<Layer> Layerdata;
    for (const auto& l : Layers) {
        Layerdata.emplace_back(l.spritepath, l.speed, l.offset, SDL->GetRenderer());
    }
	for (const auto& sfx : soundfx) {
		SFX->LoadSoundEffect(sfx.first, sfx.second);
	}
    std::string musicDirectory = "./Music/"; // Relative to the current working directory
    std::vector<std::string> audioFiles = SFX->GetAudioFiles(musicDirectory);

    int ids = 0;
    for (const auto& file : audioFiles) {
        std::cout << "Found audio file: " << file << std::endl;
		if (!SFX->LoadMusic(std::to_string(ids), file)) { SDL_Log("Failed to load music: %s", file.c_str()); }
        else { SDL_Log("Loaded music: %s", file.c_str()); ids++; }
		
    }

	for (const auto& font : FontPath) {
		TEXT->LoadFont(font.first, font.second, 20);
	}

    gameLoop(SDL, PLAYER, PATH, &event, Layerdata, SFX, TEXT);

    // Clean up
    delete PLAYER;
    delete PATH;
    delete DOG;

    return 0;
}