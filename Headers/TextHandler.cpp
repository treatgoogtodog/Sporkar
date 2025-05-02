#include "TextHandler.h"

#include <iostream>

using namespace std;
namespace fs = std::filesystem;

TextHandler::TextHandler(SDL_Renderer* renderer) : renderer(renderer) {
	if (TTF_Init() == -1) {
		cerr << "TTF_Init error at: " << TTF_GetError() << endl;
	}
}
TextHandler::~TextHandler() {
	for (auto& font : fonts) {
		TTF_CloseFont(font.second);
	}
	TTF_Quit();
}

void TextHandler::LoadFont(const std::string& id, const std::string& fontPath, int fontSize) {
	if (!fs::exists(fontPath)) {
		cerr << "Font file does not exist: " << fontPath << endl;
		return;
	}
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font) {
		cerr << "TTF_OpenFont error at: " << TTF_GetError() << endl;
		return;
	}
	fonts[id] = font;
}

void TextHandler::RenderText(const std::string& id, const std::string& text, int x, int y, SDL_Color color, int size) {
	auto it = fonts.find(id);
	if (it == fonts.end()) {
		cerr << "Font not loaded! Cannot render text!" << endl;
		return;
	}
	TTF_Font* font = it->second;
	if (TTF_SetFontSize(font, size) == -1) {
		cerr << "TTF_SetFontSize error at: " << TTF_GetError() << endl;
		return;
	}
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (!surface) {
		cerr << "TTF_RenderText_Solid error at: " << TTF_GetError() << endl;
		return;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		cerr << "SDL_CreateTextureFromSurface error at: " << SDL_GetError() << endl;
		SDL_FreeSurface(surface);
		return;
	}
	SDL_Rect dstRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

