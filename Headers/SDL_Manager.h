#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <map>

class SDL_Manager {
public:
    SDL_Manager(const std::string& windowTitle, int width, int height);
    ~SDL_Manager();

    SDL_Renderer* GetRenderer();
    SDL_Window* GetWindow();
    int GetWidth() const;
    int GetHeight() const;
    bool IsInitialized() const;

    void SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    bool IsKeyDown(SDL_Scancode key);

    // Mixer-related methods
    bool InitializeMixer(int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunksize = 2048);
    void CloseMixer();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool initialized;
    const Uint8* keyStates;
    int Width, Height;

    std::map<std::string, SDL_Texture*> textureMap; // texture
};
