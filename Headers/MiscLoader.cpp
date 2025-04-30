#include "MiscLoader.h"

std::vector<obstacledata> obstacle = {
    {"Sprite/Barricade01.png", {48, 32}, GROUND},
    {"Sprite/Barricade02.png", {32, 32}, GROUND},
    {"Sprite/Barricade03.png", {50, 48}, GROUND},
    {"Sprite/Barricade04.png", {28, 30}, GROUND},
    {"Sprite/Levietha.png", {48,48}, GROUND},
    {"Sprite/TralaleloTralala.png", {48,48}, GROUND},
    {"Sprite/GiangDam.png", {48,48}, GROUND},
    {"Sprite/Bullet.png",{64,32},AIR }
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
    {"jump2","SFX/JUMP2.wav"}
};
