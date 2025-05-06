#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <map>
#include <utility>

#include "MiscLoader.h"
#include "SoundAndMusic.h"

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
	Button(SDL_Renderer* renderer,SoundManager* SFX, SDL_Texture* texture, const map<string, SDL_Rect>& ButtonState, int x, int y, int w, int h);
	~Button();
	void render(SDL_Renderer* renderer);
	void update(int mouseX, int mouseY, int deltaTime, bool clicked);
	bool isClicked(int mouseX, int mouseY, bool clicked);
	bool isHovered(int mouseX, int mouseY);
	void Move(int x, int y);
private:
	SDL_Texture* texture;
	SoundManager* SFX;
	map<string, SDL_Rect*> Buttons;
	SDL_Rect rect = { 0,0,0,0 };
	SDL_Renderer* renderer;
	double animationProgress = 0.0;
	double currentOffsetX = 0.0;
	int x, y, w, h;
	bool clickedon;
	bool isHover = false;
	string state;
	int time;
};

class Slider {
public:
	Slider(SDL_Renderer* renderer, const string& texturePath,const string& sliderPath, int x, int y, int w, int h);
	~Slider();
	void render(SDL_Renderer* renderer);
	void update(int mouseX, int mouseY, bool clicked);
	bool isClicked(int mouseX, int mouseY, bool click);
	void setValue(float value);
	float getValue();
private:
	SDL_Texture* R_texture;
	SDL_Texture* S_texture;
	SDL_Rect rect;
	SDL_Renderer* renderer;
	int x, y, w, h;
	float value;
};

class MUTE {

};