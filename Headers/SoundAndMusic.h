
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

    void OneTimeSFX(const std::string& pth);

    void StopMusic();

    void SetSoundEffectVolume(const std::string& id, int volume);

    void SetMusicVolume(int volume);

    int GetMusicCount() const;

    int GetCustomCount() const;

    int GetThemeCount() const;

    void CleanUp();

    void AddToCustom();

    void AddToTheme();

    void AddThemeInfo(std::string info);

    std::pair<int, int> GetVolume() const;

private:
    std::map<std::string, Mix_Chunk*> soundEffects; 
    std::map<std::string, Mix_Music*> musicTracks;

    int CustomMusicCounter;
    int ThemeMusicCounter;
    std::vector<std::string> themeInfo;

    int musicVolume;
	int soundEffectVolume;
};

