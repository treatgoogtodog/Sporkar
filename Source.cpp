#include "SDL_Manager.h"
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Manager sdlManager("Wannabe gamaer", 800, 600);

    if (!sdlManager.IsInitialized()) {
        std::cerr << "Failed to initialize SDL." << std::endl;
        return 1;
    }

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Kiểm tra trạng thái phím 'W'
        if (sdlManager.IsKeyDown(SDL_SCANCODE_W)) {
            std::cout << "Key 'W' is being held down!" << std::endl;
        }

        // Kiểm tra trạng thái phím ESC để thoát
        if (sdlManager.IsKeyDown(SDL_SCANCODE_ESCAPE)) {
            std::cout << "Escape key pressed. Exiting!" << std::endl;
            running = false;
        }

        // Cập nhật màn hình
        SDL_SetRenderDrawColor(sdlManager.GetRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(sdlManager.GetRenderer());
        SDL_RenderPresent(sdlManager.GetRenderer());
    }

    return 0;
}
