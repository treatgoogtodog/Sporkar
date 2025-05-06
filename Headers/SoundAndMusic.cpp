#include "SoundAndMusic.h"
#include <iostream>

namespace fs = std::filesystem;

SoundManager::SoundManager() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
	this->CustomMusicCounter = 0;
	this->ThemeMusicCounter = 0;
	this->musicVolume = MIX_MAX_VOLUME/2;
	this->soundEffectVolume = MIX_MAX_VOLUME / 2;
}

SoundManager::~SoundManager() {
    CleanUp();
    Mix_CloseAudio();
}

std::vector<std::string> SoundManager::GetAudioFiles(const std::string& directory) {
	std::vector<std::string> audioFiles;

    try {
        for (const auto& entry : fs::directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                std::string filePath = entry.path().string();
                std::string __extension = filePath.substr(filePath.find_last_of(".") + 1);
                if (__extension == "mp3" || __extension == "ogg" || __extension == "wav") {
                    audioFiles.push_back(filePath);
                }
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error reading directory: " << e.what() << std::endl;
    }
    return audioFiles;
}


bool SoundManager::LoadSoundEffect(const std::string& id, const std::string& filePath) {
    Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
    if (!chunk) {
        std::cerr << "Failed to load sound effect: " << filePath << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    soundEffects[id] = chunk;
    return true;
}

bool SoundManager::LoadMusic(const std::string& id, const std::string& filePath) {
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << filePath << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    musicTracks[id] = music;
    return true;
}


void SoundManager::PlaySoundEffect(const std::string& id, int loops) {
    auto it = soundEffects.find(id);
    if (it != soundEffects.end()) {
        Mix_PlayChannel(-1, it->second, loops);
    } else {
        std::cerr << "Sound effect with ID '" << id << "' not found!" << std::endl;
    }
}


void SoundManager::PlayMusic(const std::string& id, int loops) {
    auto it = musicTracks.find(id);
    if (it != musicTracks.end()) {
        if (Mix_PlayMusic(it->second, loops) == -1) {
            std::cerr << "Failed to play music with ID '" << id << "': " << Mix_GetError() << std::endl;
		}
    } else {
        std::cerr << "Music with ID '" << id << "' not found!" << std::endl;
    }
}

void SoundManager::OneTimeSFX(const std::string& pth) {
	Mix_Chunk* chunk = Mix_LoadWAV(pth.c_str());
	if (chunk) {
		Mix_PlayChannel(-1, chunk, 0);
		Mix_FreeChunk(chunk);
	}
	else {
		std::cerr << "Failed to load sound effect: " << pth << "|" << Mix_GetError() << std::endl;
	}
}

void SoundManager::StopMusic() {
    Mix_HaltMusic();
}

void SoundManager::SetSoundEffectVolume(const std::string& id, int volume) {
    auto it = soundEffects.find(id);
    if (it != soundEffects.end()) {
        Mix_VolumeChunk(it->second, volume);
    } else {
        std::cerr << "Sound effect with ID '" << id << "' not found!" << std::endl;
    }
}

void SoundManager::SetMusicVolume(int volume) {
    Mix_VolumeMusic(volume);
}

void SoundManager::CleanUp() {
    for (auto& pair : soundEffects) {
        Mix_FreeChunk(pair.second);
    }
    soundEffects.clear();

    for (auto& pair : musicTracks) {
        Mix_FreeMusic(pair.second);
    }
    musicTracks.clear();
}

int SoundManager::GetMusicCount() const{
	return musicTracks.size();
}

int SoundManager::GetCustomCount() const {
    return this->CustomMusicCounter;
}

int SoundManager::GetThemeCount() const {
    return this->ThemeMusicCounter;
}

void SoundManager::AddToCustom() {
    CustomMusicCounter++;
}

void SoundManager::AddToTheme() {
    ThemeMusicCounter++;
}

void SoundManager::AddThemeInfo(std::string info) {
    this->themeInfo.push_back(info);
}

std::pair<int, int> SoundManager::GetVolume() const {
	return std::make_pair(this->musicVolume, this->soundEffectVolume);
}
