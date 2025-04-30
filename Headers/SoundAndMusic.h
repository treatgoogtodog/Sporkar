
#pragma once

#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <filesystem>
#include <map>

class SoundManager {
public:
    
    SoundManager();
    ~SoundManager();

    std::vector<std::string> GetAudioFiles(const std::string& directory);

    bool LoadSoundEffect(const std::string& id, const std::string& filePath);

    bool LoadMusic(const std::string& id, const std::string& filePath);

    void PlaySoundEffect(const std::string& id, int loops = 0);

    void PlayMusic(const std::string& id, int loops = -1);

    void StopMusic();

    void PauseMusic();

    void ResumeMusic();

    void SetSoundEffectVolume(const std::string& id, int volume);

    void SetMusicVolume(int volume);

    void CleanUp();

private:
    std::map<std::string, Mix_Chunk*> soundEffects; 
    std::map<std::string, Mix_Music*> musicTracks;
};

