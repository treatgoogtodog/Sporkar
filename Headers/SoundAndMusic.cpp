#include "SoundAndMusic.h"
#include <iostream>

namespace fs = std::filesystem;

SoundManager::SoundManager() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
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
                std::string __extension = filePath.substr(filePath.find_last_not_of(".") + 1);
                if (__extension == "mp3" || __extension == "ogg") {
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

// Play a sound effect
void SoundManager::PlaySoundEffect(const std::string& id, int loops) {
    auto it = soundEffects.find(id);
    if (it != soundEffects.end()) {
        Mix_PlayChannel(-1, it->second, loops);
    } else {
        std::cerr << "Sound effect with ID '" << id << "' not found!" << std::endl;
    }
}

// Play music
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
    

// Stop music
void SoundManager::StopMusic() {
    Mix_HaltMusic();
}

// Pause music
void SoundManager::PauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

// Resume music
void SoundManager::ResumeMusic() {
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}

// Set volume for a specific sound effect
void SoundManager::SetSoundEffectVolume(const std::string& id, int volume) {
    auto it = soundEffects.find(id);
    if (it != soundEffects.end()) {
        Mix_VolumeChunk(it->second, volume);
    } else {
        std::cerr << "Sound effect with ID '" << id << "' not found!" << std::endl;
    }
}

// Set volume for music
void SoundManager::SetMusicVolume(int volume) {
    Mix_VolumeMusic(volume);
}

// Clean up all loaded sounds and music
void SoundManager::CleanUp() {
    // Free all sound effects
    for (auto& pair : soundEffects) {
        Mix_FreeChunk(pair.second);
    }
    soundEffects.clear();

    // Free all music tracks
    for (auto& pair : musicTracks) {
        Mix_FreeMusic(pair.second);
    }
    musicTracks.clear();
}
