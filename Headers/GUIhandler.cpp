#include "GUIhandler.h"


GUIhandler::GUIhandler(SDL_Renderer* renderer, int w_width, int w_height){
	this->renderer = renderer;
	this->width = w_width;
	this->height = w_height;
	OverLay = IMG_LoadTexture(renderer, "Sprite/GUI/Overlay.png");
	if (!OverLay) {
		SDL_Log("Failed to load overlay texture: %s", IMG_GetError());
	}
}

GUIhandler::~GUIhandler() {
	if (OverLay) {
		SDL_DestroyTexture(OverLay);
	}
	for (auto& pair : ElementTXT) {
		SDL_DestroyTexture(pair.second);
	}
}

void GUIhandler::LoadOverLay(const std::string& texturePath) {
	OverLay = IMG_LoadTexture(renderer, texturePath.c_str());
	if (!OverLay) {
		SDL_Log("Failed to load overlay texture: %s", IMG_GetError());
	}
}

void GUIhandler::LoadElement(const std::string& id, const std::string& texturePath) {
	SDL_Texture* texture = IMG_LoadTexture(renderer, texturePath.c_str());
	if (!texture) {
		SDL_Log("Failed to load element texture: %s", IMG_GetError());
		return;
	}
	ElementTXT[id] = texture;
}
void GUIhandler::render(SDL_Renderer* renderer, float HealthP, float SkillP) {
	if (OverLay) {
		SDL_RenderCopy(renderer, OverLay, nullptr, nullptr);
	}
	pair<int, int> HPOS = { 18,22 };
	if (ElementTXT["Health"]) {
		SDL_Rect healthRect = { HPOS.first, HPOS.second, 343 * HealthP, 26 };
		SDL_Rect scrRect = { 0, 0, 343*HealthP, 26 };
		SDL_RenderCopy(renderer, ElementTXT["Health"], &scrRect, &healthRect);
	}
	pair<int, int> SPOS = { 18,58 };
	if (ElementTXT["Skill"]) {
		SDL_Rect skillRect = { SPOS.first, SPOS.second, 309 * SkillP, 26 };
		SDL_Rect scrRect = { 0, 0, 309 * SkillP, 26 };
		SDL_RenderCopy(renderer, ElementTXT["Skill"], &scrRect, &skillRect);
	}
}

