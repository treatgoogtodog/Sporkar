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
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!renderer) {
			std::cout << "Renderer Creation Error:" << SDL_GetError() << std::endl;
			return;
		}
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
			std::cout << "IMG_Init Err" << SDL_GetError() << std::endl;
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
		keyStates = SDL_GetKeyboardState(nullptr);
		initialized = true;
}

SDL_Manager::~SDL_Manager() {
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool SDL_Manager::IsKeyDown(SDL_Scancode key) {
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
	return keyStates[key];
}

SDL_Renderer* SDL_Manager::GetRenderer() {
	return renderer;
}

SDL_Window* SDL_Manager::GetWindow() {
	return window;
}

bool SDL_Manager::IsInitialized() const {
	return initialized;
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

const Uint8* keyStates;

bool KeycheckPressed(SDL_Scancode key) {
	keyStates = SDL_GetKeyboardState(nullptr);
	return keyStates[key];
}