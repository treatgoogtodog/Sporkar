#pragma once

#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "Animation.h"
#include "MappingSystem.h"
#include <map>
#include <vector>
using json = nlohmann::json;

std::map<std::string, Animation> SheetReader(const std::string& jsonpath, const std::string& sheetpath, SDL_Renderer* renderer, SDL_Texture*& TEXTURE);

//Loading map. map here is a set of possiblities that's making the run looks differents with random-generated seeds (or "I played these game before")
std::map<int,mapSQ> MapReader(const std::string& path);