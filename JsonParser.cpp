
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "Animation.h"
#include "JsonParsers.h"
#include "json.hpp"
using json = nlohmann::json;

std::map<std::string, Animation> SheetReader(const std::string& jsonpath, const std::string& sheetpath, SDL_Renderer* renderer, SDL_Texture*& TEXTURE) {
    TEXTURE = LoadTexture(renderer, sheetpath);
    if (TEXTURE == nullptr) {
        std::cout << "Error reading spritesheet at " << sheetpath << std::endl;
        return std::map<std::string, Animation>();
    }
    std::ifstream file(jsonpath);
    if (!file.is_open()) {
        std::cout << "Error reading jsonfile at " << jsonpath << std::endl;
        return std::map<std::string, Animation>();
    }
    std::map<std::string, Animation> animation;
    json jsonData;
    file >> jsonData;

    for (const auto& [animationName, frames] : jsonData["animations"].items()) {
        Animation Temp;
        for (const auto& frame : frames) {
            Frame f = { frame["x"], frame["y"], frame["w"], frame["h"] };
            Temp.addframe(f);
        }
        Temp.texture = TEXTURE;
        animation[animationName] = Temp;
    }
    return animation;
}
