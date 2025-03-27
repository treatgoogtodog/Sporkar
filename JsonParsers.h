#pragma once

#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "Animation.h"
#include <map>
using json = nlohmann::json;

std::map<std::string, Animation> SheetReader(const std::string& jsonpath, const std::string& sheetpath, SDL_Renderer* renderer, SDL_Texture*& TEXTURE);
