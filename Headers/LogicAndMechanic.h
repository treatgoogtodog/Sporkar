#pragma once

#include "CharacterSystem.h"
#include "Object.h"
#include "SDL_Manager.h"
#include "MiscLoader.h"

using namespace std;

void gameLoad(SDL_Manager* SDL, Player*& PLAYER);

void gameLoop(SDL_Manager* SDL, Player* PLAYER, PathManager* PATH, SDL_Event* event);