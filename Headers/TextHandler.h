#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <filesystem>
#include <string>
#include <map>

class TextHandler {
public:
	TextHandler(SDL_Renderer* renderer);
	~TextHandler();

	void LoadFont(const std::string& id, const std::string& fontPath, int fontSize);

	void RenderText(const std::string& id, const std::string& text, int x, int y, SDL_Color color, int size);

private:
	SDL_Renderer* renderer;
	std::map<std::string, TTF_Font*> fonts;
};