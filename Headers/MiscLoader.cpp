#include "MiscLoader.h"

std::vector<obstacledata> obstacle = {
	{"Sprite/roadobs/block1.png", {86, 64}, 1},
	{"Sprite/roadobs/block2.png", {64, 64}, 1},
	{"Sprite/roadobs/block3.png", {64, 64}, 1},
	{"Sprite/roadobs/block4.png", {64, 64}, 1},
	{"Sprite/roadobs/block5.png", {64, 64}, 1},
	{"Sprite/roadobs/block6.png", {86, 64}, 1},
	{"Sprite/roadobs/block7.png", {86, 64}, 1},
	{"Sprite/roadobs/block8.png", {64, 64}, 1},
	{"Sprite/roadobs/block9.png", {64, 64}, 1},
	{"Sprite/roadobs/block10.png", {100, 64}, 1},
	{"Sprite/aerialobs/bullet1.png",{100,32}, 0},
	{"Sprite/aerialobs/bullet2.png",{100,32}, 0}
};

std::vector<PowerUpdata> powerup = {
	{"Sprite/PowerUp/Hyper.png", {48, 48}, HYPER },
	{ "Sprite/PowerUp/Nuke.png", {48, 48}, NUKE },
	{ "Sprite/PowerUp/Gamble.png", {48, 48}, GAMBLE }
};

std::vector<layer> Layers = {
     {"Sprite/Bg/1.png", 0.1f, 0},  
    {"Sprite/Bg/2.png", 0.25f, 0},
    {"Sprite/Bg/3.png", 0.5f, 0},
    {"Sprite/Bg/4.png", 0.75f, 0},
    {"Sprite/Bg/5.png", 1.0f, 0}
};

std::vector<std::pair<std::string, std::string>> soundfx = {
    {"hurt1","SFX/HURT1.wav"},
    {"hurt2","SFX/HURT2.wav"},
    {"hurt3","SFX/HURT3.wav"},
    {"hurt4","SFX/HURT4.wav"},
    {"jump1","SFX/JUMP1.wav"},
    {"jump2","SFX/JUMP2.wav"},
	{"click","SFX/click.wav"},
	{"hover","SFX/hover.wav"},
	{"select","SFX/select.wav"},
	{"pickup1","SFX/pickup1.wav"},
	{"pickup2","SFX/pickup2.wav"}
};

std::vector<std::pair<std::string, std::string>> voicelinefx = {
	{"voice01", "Voiceline/bystander.wav"},
	{"voice02", "Voiceline/dontlikegames.wav"},
	{"voice03", "Voiceline/grandmother.wav"},
	{"voice04", "Voiceline/whereisnapalm.wav"},
	{"voice05", "Voiceline/whoeverdesigned.wav"}
};
 
std::vector<std::pair<std::string, std::string>> FontPath = {
	{"Special", "Fonts/ExtraWide.ttf"},
	{"Bold", "Fonts/HachicroUndertale.ttf"},
	{"Default", "Fonts/Pixelpurl.ttf"}
};

std::map<std::string, SDL_Rect> startButton = {
    {"IDLE",  {273, 130, 272, 66}},
    {"CLICK", {0, 131, 272, 64}},
    {"HOVER", {548, 0, 274, 66}}
};

std::map<std::string, SDL_Rect> hscoreButton = {
    {"IDLE",  {0, 195, 272, 63}},
    {"CLICK", {0, 66, 273, 65}},
    {"HOVER", {273, 66, 273, 64}}
};

std::map<std::string, SDL_Rect> quitButton = {
    {"IDLE",  {274, 0, 274, 66}},
    {"CLICK", {0, 0, 274, 66}},
    {"HOVER", {546, 66, 273, 64}}
};


std::vector <std::map<std::string, SDL_Rect>> ButtonState = {
	startButton,
	hscoreButton,
	quitButton
};

std::vector <std::pair<std::string, std::string>> ThemeMusics = {
	{"TMusic/Porter Robinson - Sea of Voices.mp3", "Porter Robinson - Sea of Voices"},
	{"TMusic/d4vd - Feel It.mp3", "d4vd - Fell It"},
	{"TMusic/Let It Happen.mp3", "Tame Impala - Let It Happen"},
	{"TMusic/Evanescence - Afterlife.mp3", "Evanescence - Afterlife"}
};