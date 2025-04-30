#include "CharacterSystem.h"

using namespace std;

Player::Player(int x, int y, const std::string& texturePTH, const std::string& textureDAT, SDL_Renderer* renderer, const float& multipler) {
	this->x = x;
	this->y = y;
	this->texturedata = SheetReader(textureDAT, texturePTH, renderer, texture);
	this->width = texturedata["Run"].frames[0].width;
	this->height = texturedata["Run"].frames[0].height;
	this->VelY = 0;
	this->curr_anim = "Idle";
	this->health = 100;
	this->multipler = multipler;
	SDL_SetTextureAlphaMod(texture, 255);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

Player::~Player() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

bool Player::update(bool isJumping, float gravity, float JumpStreg, int groundLvl) {
	bool jump = false;
	if (isJumping && y == groundLvl) {
		VelY = -JumpStreg;
		jump = true;
	}

	VelY += gravity; 
	y += static_cast<int>(VelY);

	if (y > groundLvl) {
		y = groundLvl;
		VelY = 0;
	}
	if (this->y < groundLvl) {
		curr_anim = "Jump";
		UpdateIDs(isJumping);
	}
	else {
		curr_anim = "Run";
		}
	return jump;
}

void Player::render(SDL_Renderer* renderer, const int& deltaTime, const float& multipler) {
	UpdateAnimation(this->texturedata[curr_anim], deltaTime);
	if(IDs == -1){
		DrawAnimation(renderer, this->texturedata[curr_anim], this->x, this->y, multipler);
	}
	else {
		DrawAnimFrame(renderer, this->texturedata[curr_anim], this->x, this->y, IDs, multipler);
	}
	
}

void Player::UpdateIDs(bool isJumping){
	if (!isJumping) { this->IDs = -1; return; }
	if (VelY >= 0.5) { this->IDs = 0; return; }
	if ((VelY < 0.5) && (VelY > -0.5)) { this->IDs = 1; return; }
	if (VelY <= 0.5) { this->IDs = 1; return; }
}

