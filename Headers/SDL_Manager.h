#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class SDL_Manager {
public:
    SDL_Manager(const std::string& windowTitle, int width, int height);
    ~SDL_Manager();


    SDL_Renderer* GetRenderer();
    SDL_Window* GetWindow();
    bool IsInitialized() const;

    
    
    void SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    bool IsKeyDown(SDL_Scancode key);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool initialized;
    const Uint8* keyStates;

    std::map<std::string, SDL_Texture*> textureMap; // texture
};
