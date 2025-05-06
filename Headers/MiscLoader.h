#pragma once  
#include <string>  
#include <vector>  
#include <utility> 
#include "Animation.h"  
#include <SDL_mixer.h>  
#include "TextHandler.h"


#define PLAYERSPRITEPATH "Sprite\\PlayerSpr\\BlackinMan.png"  
#define PLAYERSPRITESHEETDATA "Sprite\\PlayerSpr\\BlackinMan.json"  
#define GROUNDSPRITEPATH "Sprite\\Road.png"  
#define DOGDOGSPITEPATH "Sprite\\Dogdog.png"  
#define DOGDOGSHEETDATA "Sprite\\Dogdog.json"  

#define OVERLAYPATH "Sprite\\GUI\\Overlay.png"
#define HEALTHBARPATH "Sprite\\GUI\\Health.png"
#define SKILLBARPATH "Sprite\\GUI\\Skill.png"

#define HEALTHPOS = {18,22}
#define SKILLPOS = {18,58}

struct obstacledata {  
   std::string spritepath;  
   std::pair<int, int> size;  
   int type;
};  

struct layer {  
   std::string spritepath;  
   float speed;  
   int offset;  
};  

extern std::vector<obstacledata> obstacle;  

extern std::vector<layer> Layers;  

extern std::vector<std::pair<std::string, std::string>> soundfx; 

extern std::vector<std::pair<std::string, std::string>> voicelinefx;

extern std::vector<std::pair<std::string, std::string>> FontPath;

extern std::map<std::string, SDL_Rect> startButton;

extern std::map<std::string, SDL_Rect> hscoreButton;

extern std::map<std::string, SDL_Rect> quitButton;

extern std::vector <std::map<std::string, SDL_Rect>> ButtonState;

extern std::vector <std::pair<std::string, std::string>> ThemeMusics;

//extern std::vector<std::map<std::string, SDL_Rect>> resumeButton;
//
//extern std::vector<std::map<std::string, SDL_Rect>> quitsButton;
//
//extern std::vector<std::map<std::string, SDL_Rect>> titleButton;