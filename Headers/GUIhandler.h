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

class Button {
public:
	Button(SDL_Renderer* renderer, const string& texturePath, const map<string, SDL_Rect>& ButtonState, int x, int y, int w, int h);
	~Button();
	void render(SDL_Renderer* renderer);
	bool isClicked(int mouseX, int mouseY);
	bool isHovered(int mouseX, int mouseY);
private:
	SDL_Texture* texture;
	map<string, SDL_Rect*> Buttons;
	SDL_Rect rect;
	SDL_Renderer* renderer;
	int x, y, w, h;
	bool clickedon;
	string state;
};

class Slider {
public:
	Slider(SDL_Renderer* renderer, const string& texturePath, int x, int y, int w, int h);
	~Slider();
	void render(SDL_Renderer* renderer);
	bool isClicked(int mouseX, int mouseY);
	bool isHovered(int mouseX, int mouseY);
	void setValue(float value);
	float getValue();
private:
	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Renderer* renderer;
	int x, y, w, h;
	bool clickedon;
	float value;
};