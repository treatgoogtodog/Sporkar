#pragma once
#include <string>
#include <vector>
#include "Animation.h"

// ALL PATHS ARE RELATED TO SOURCE

#define PLAYERSPRITEPATH "Sprite\\BlackinMan.png"
#define PLAYERSPRITESHEETDATA "Texture\\PlayerTexture.json"
#define GROUNDSPRITEPATH "Sprite\\Road.png"

struct obstacledata {
    std::string spritepath;
    std::pair<int, int> size; // width, height
};

extern std::vector<obstacledata> obstacle;

struct LayerData {
    std::string spritepath;
    float speed;
    float offset;
};

extern std::vector<LayerData> Layers;
