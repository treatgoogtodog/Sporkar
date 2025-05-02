#pragma once  
#include <string>  
#include <vector>  
#include <utility> 
#include "Animation.h"  
#include <SDL_mixer.h>  
#include "TextHandler.h"

// ALL PATHS ARE RELATED TO SOURCE  

#define PLAYERSPRITEPATH "Sprite\\PlayerSpr\\BlackinMan.png"  
#define PLAYERSPRITESHEETDATA "Sprite\\PlayerSpr\\BlackinMan.json"  
#define GROUNDSPRITEPATH "Sprite\\Road.png"  
#define DOGDOGSPITEPATH "Sprite\\Dogdog.png"  
#define DOGDOGSHEETDATA "Sprite\\Dogdog.json"  

enum ObsType {  
   AIR,  
   GROUND  
};  

struct obstacledata {  
   std::string spritepath;  
   std::pair<int, int> size;  
   ObsType type; // width, height  
};  

struct layer {  
   std::string spritepath;  
   float speed;  
   int offset;  
};  

extern std::vector<obstacledata> obstacle;  

extern std::vector<layer> Layers;  

extern std::vector<std::pair<std::string, std::string>> soundfx; 

extern std::vector<std::pair<std::string, std::string>> FontPath;