#pragma once

#include "CharacterSystem.h"
#include "Object.h"
#include "SDL_Manager.h"
#include "SoundAndMusic.h"
#include "MiscLoader.h"
#include "TextHandler.h"
#include "GUIhandler.h"

#include <random>
#include <stdio.h>


enum GAMESTATE
{
	MENU, GAME, PAUSE, EXIT, LOSS
};

struct GAMELOOPDATA {
	SDL_Manager* SDL;
	Player* PLAYER;
	PathManager* PATH;
	SDL_Event* event;
	std::vector<Layer>& backgroundLayers;
	SoundManager* SFX;
	TextHandler* TEXT;
	GUIhandler* GUI;
};

using namespace std;

int DRNG(int bot, int top);

GAMESTATE gameLoop(SDL_Manager* SDL, Player* PLAYER, PathManager* PATH, SDL_Event* event, std::vector<Layer>& backgroundLayers, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI);

GAMESTATE GamePause(SDL_Manager* SDL, SDL_Event* event, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI, GAMELOOPDATA gamedata);

GAMESTATE Menu(SDL_Manager* SDL, SDL_Event* event, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI, GAMELOOPDATA gamedata);

GAMESTATE GameOver(SDL_Manager* SDL, SDL_Event* event, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI, GAMELOOPDATA gamedata);

void ScoreBoard(GAMELOOPDATA gamedata, string savPth);

void WriteScore(const std::string& filePath, int newScore);