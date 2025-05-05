#pragma once

#include "CharacterSystem.h"
#include "Object.h"
#include "SDL_Manager.h"
#include "SoundAndMusic.h"
#include "MiscLoader.h"
#include "TextHandler.h"
#include "GUIhandler.h"
#include <random>


using namespace std;

int DRNG(int bot, int top);

void gameLoad(SDL_Manager* SDL, Player*& PLAYER, dog*& DOG, SoundManager SFX, std::vector<std::pair<std::string, std::string>> sfxdata);

void gameLoop(SDL_Manager* SDL, Player* PLAYER, PathManager* PATH, SDL_Event* event, std::vector<Layer>& backgroundLayers, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI);

void pauseGame(SDL_Manager* SDL, Player* PLAYER, PathManager* PATH, SDL_Event* event, std::vector<Layer>& backgroundLayers, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI);

void Menu(SDL_Manager* SDL, SDL_Event* event, std::vector<Layer>& backgroundLayers, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI);