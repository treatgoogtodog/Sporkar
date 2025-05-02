#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <utility>

#include "MiscLoader.h"

using namespace std;

class GUIhandler {
public:
	GUIhandler(SDL_Renderer* renderer, int w_width, int w_height);
	~GUIhandler();
	void LoadOverLay(const std::string& texturePath);
	void LoadElement(const std::string& id, const std::string& texturePath);
	void render(SDL_Renderer* renderer,float HealthP, float SkillP);
private:
	SDL_Texture* OverLay;
	map<string, SDL_Texture*> ElementTXT;
	SDL_Renderer* renderer;
	int width, height;
};