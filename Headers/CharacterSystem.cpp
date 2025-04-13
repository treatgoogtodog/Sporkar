#include "CharacterSystem.h"

using namespace std;

player::player(int x, int y, const std::string& texturePTH, const std::string& textureDAT, SDL_Renderer* renderer) {
	this->x = x;
	this->y = y;
	this->texturedata = SheetReader(textureDAT, texturePTH, renderer, texture);
	this->width = texturedata["Idle"].frames[0].width;
	this->height = texturedata["Idle"].frames[0].height;
	this->VelY = 0;
	this->curr_anim = "Idle";
}

player::~player() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void player::update(bool isJumping, float gravity, float JumpStreg, int groundLvl) {
	if (isJumping && y == groundLvl) {
		VelY = -JumpStreg;
	}

	VelY += gravity; 
	y += static_cast<int>(VelY);

	if (y > groundLvl) {
		y = groundLvl;
		VelY = 0;
	}
}

void player::render(SDL_Renderer* renderer, const int& deltaTime) {
	UpdateAnimation(this->texturedata[curr_anim], deltaTime);
	if(IDs == -1){
		DrawAnimation(renderer, this->texturedata[curr_anim], this->x, this->y);
	}
	else {
		DrawAnimFrame(renderer, this->texturedata[curr_anim], this->x, this->y, IDs);
	}
	
}

void player::UpdateIDs(bool isJumping){
	if (!isJumping) { this->IDs = -1; return; }
	if (VelY >= 0.5) { this->IDs = 0; return; }
	if ((VelY < 0.5) && (VelY > -0.5)) { this->IDs = 1; return; }
	if (VelY <= 0.5) { this->IDs = 1; return; }
}

