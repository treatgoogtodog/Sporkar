#include <iostream>
#include <string>

#include "SDL_Manager.h"

SDL_Manager::SDL_Manager(const std::string& windowTitle, int width, int height) :window(nullptr), renderer(nullptr), initialized(false) {
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
		
		this->Width = width;
		this->Height = height;
}

SDL_Manager::~SDL_Manager() {

	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
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

void SDL_Manager::SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	if (renderer) {
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderClear(renderer);
	}
}

int SDL_Manager::GetWidth() const {
    return Width;
}

int SDL_Manager::GetHeight() const {
    return Height;
}

bool SDL_Manager::IsKeyDown(SDL_Scancode key) {
    keyStates = SDL_GetKeyboardState(nullptr);
    return keyStates[key];
}

