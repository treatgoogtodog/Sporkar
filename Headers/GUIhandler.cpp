#include "GUIhandler.h"


GUIhandler::GUIhandler(SDL_Renderer* renderer, int w_width, int w_height)
	:renderer(renderer), width(w_width), height(w_height) {
		{
			OverLay = IMG_LoadTexture(renderer, "Sprite/GUI/Overlay.png");
			if (!OverLay) {
				SDL_Log("Failed to load overlay texture: %s", IMG_GetError());
			}
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

void GUIhandler::RenderSingle(SDL_Renderer* renderer, std::string& id, int x, int y, int w, int h) {
	SDL_Rect* destRect;
	if (w == 0 && h == 0) {
		destRect = NULL;
	}
	else {
		destRect = new SDL_Rect();
		destRect->x = x;
		destRect->y = y;
		destRect->w = w;
		destRect->h = h;
	}
	
	SDL_RenderCopy(renderer, ElementTXT[id], nullptr, destRect);
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
		SDL_Rect skillRect = { SPOS.first, SPOS.second, static_cast<int>(309 * SkillP), 26 };
		SDL_Rect scrRect = { 0, 0, static_cast<int>(309 * SkillP), 26 };
		SDL_RenderCopy(renderer, ElementTXT["Skill"], &scrRect, &skillRect);
	}
}

Button::Button(SDL_Renderer* renderer,SoundManager* SFX, SDL_Texture* texture,const map<string, SDL_Rect>& ButtonState, int x, int y, int w, int h)
	:renderer(renderer), x(x), y(y), w(w), h(h), time(0), texture(texture) {
	for (const auto& state : ButtonState) {
		Buttons[state.first] = new SDL_Rect(state.second);
	}
	this->clickedon = false;
	this->isHover = false;
	this->state = "IDLE";
	this->rect = { x, y, w, h };
	this->SFX = SFX;
}

Button::~Button() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
	for (auto& pair : Buttons) {
		delete pair.second;
	}
}

void Button::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, Buttons[state], &rect);
}

void Button::Move(int x, int y) {
	this->x = x;
	this->y = y;
	this->rect.x = x;
	this->rect.y = y;
}

void Button::update(int mouseX, int mouseY, int deltaTime, bool clicked) {
	double effspeed = 0.1f;
	string last_state = state;
	double duration = 700;
	int TargetX_offset = -30;
	
	double delta = static_cast<double>(deltaTime) / 10.0;
	if (isHovered(mouseX, mouseY)) {
		isHover = true;
		
		if (isClicked(mouseX, mouseY, clicked)) {
			state = "CLICK";
			if (last_state != state) {
				SFX->PlaySoundEffect("select");
				last_state = state;
			}
		}
		else {
			state = "HOVER";
			if (last_state != state) {
				SFX->PlaySoundEffect("hover");
				last_state = state;
			}
		}
	}
	else {
		isHover = false;
		state = "IDLE";
		last_state = state;
	}

	if (isHover) {
		animationProgress += effspeed * delta;
		if (animationProgress > 1.0) {
			animationProgress = 1.0;
		}
	}
	else {
		animationProgress -= effspeed * delta;
		if (animationProgress < 0.0) {
			animationProgress = 0.0;
		}
	}
	currentOffsetX = TargetX_offset * (1 - (1 - animationProgress) * (1 - animationProgress));
	rect.x = this->x + static_cast<int>(currentOffsetX);
}

bool Button::isClicked(int mouseX, int mouseY, bool clicked) {
	if (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h) {
		if (clicked) {
			state = "CLICK";
			return clicked;
		}
	}
	clickedon = false;
	return false;
}

bool Button::isHovered(int mouseX, int mouseY) {
	if (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h) {
		state = "HOVER";
		return true;
	}
	state = "IDLE";
	return false;
}

Slider::Slider(SDL_Renderer* renderer, const string& texturePath, const string& SliderPath, int x, int y, int w, int h)
	:renderer(renderer), x(x), y(y), w(w), h(h), value(0.0f) {
	this->R_texture = IMG_LoadTexture(renderer, texturePath.c_str());
	this->S_texture = IMG_LoadTexture(renderer, SliderPath.c_str());
	if (!this->R_texture||!this->S_texture) {
		SDL_Log("Failed to load slider texture: %s", IMG_GetError());
	}

	this->rect = { x, y, w, h };
	
}

Slider::~Slider() {
	if (R_texture) {
		SDL_DestroyTexture(R_texture);
	}
	if (S_texture) {
		SDL_DestroyTexture(S_texture);
	}
}

void Slider::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, R_texture, nullptr, &rect);
	int S_w, S_h;
	SDL_QueryTexture(S_texture, NULL, NULL, &S_w, &S_h);
	SDL_Rect destSliderRect = { x + static_cast<int>(value * w), y-6, S_w, S_h};
	SDL_RenderCopy(renderer, S_texture, nullptr, &destSliderRect);
}

void Slider::setValue(float value) {
	this->value = SDL_clamp(value, 0.0f, 1.0f);
}

bool Slider::isClicked(int mouseX, int mouseY, bool click) {
	if (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h) {
		return click;
	}
	return false;
}

void Slider::update(int mouseX, int mouseY, bool clicked) {
	if (isClicked(mouseX, mouseY, clicked)) {
		value = static_cast<float>(mouseX - x) / static_cast<float>(w);
	}
	value = SDL_clamp(value, 0.0f, 1.0f);
}


float Slider::getValue() {
	return value;
}