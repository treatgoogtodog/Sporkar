#include <iostream>
#include <string>

#include "SDL_Manager.h"

SDL_Manager::SDL_Manager(const std::string& windowTitle, int width, int height) :window(nullptr), renderer(nullptr), initialized(false) {
	//init
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Initialization Error:" << SDL_GetError() << std::endl;
		return;
	}
	window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		if (!window) {
			std::cout << "Window Creation Error:" << SDL_GetError() << std::endl;
			return;
		}
	
}


void HandleKeyboardEvent(const SDL_Event& event) {
	switch (event.type) {
	case SDL_KEYDOWN:
		if (!event.key.repeat) {
			std::cout << "Key pressed: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
		}
		break;

	case SDL_KEYUP:
		std::cout << "Key released: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
		break;

	default:
		break;
	}
}

static const Uint8* keyStates;

bool KeycheckPressed(SDL_Scancode key) {
	keyStates = SDL_GetKeyboardState(nullptr);
	return keyStates[key];
}