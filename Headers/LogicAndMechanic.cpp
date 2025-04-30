#include "LogicAndMechanic.h"


void gameLoop(SDL_Manager* SDL, Player* PLAYER, PathManager* PATH, SDL_Event* event, std::vector<Layer>& backgroundLayers, SoundManager* SFX) {
    bool gameover = false;
    bool quit = false;
    int intervalSpawn = 1200;
    int spawnTime = 0;
    int gameTime = 0;
    int previousTime = SDL_GetTicks();
    int speed = 5;

    SDL_Texture* groundTexture = LoadTexture(SDL->GetRenderer(), GROUNDSPRITEPATH);

    while (!quit && !gameover) {
        int currentTime = SDL_GetTicks();
        int deltaTime = currentTime - previousTime;

        while (SDL_PollEvent(event)) {
            if (event->type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(SDL->GetRenderer());

        // Render parallax background with deltaTime and speed
        RenderParallaxBackground(SDL->GetRenderer(), backgroundLayers, 800, 600, deltaTime, speed);

        // Update player and game logic
        bool isJumping = SDL->IsKeyDown(SDL_SCANCODE_SPACE);
        float gravity = 0.5f;
        float jumpStrength = 10.0f;
        int groundLevel = 300;
        bool jump = PLAYER->update(isJumping, gravity, jumpStrength, groundLevel);

        if (gameTime >= 3000) {
            speed += 1;
            gameTime = 0;
            std::cout << "Speed: " << speed << std::endl;
        }

        PATH->UPDATE(SDL->GetRenderer(), speed);
        spawnTime += deltaTime;

        if (spawnTime >= intervalSpawn) {
            int randomIndex = rand() % obstacle.size();
            PATH->addNewObject(800, 300, obstacle[randomIndex].size.first, obstacle[randomIndex].size.second, obstacle[randomIndex].spritepath, SDL->GetRenderer());
            spawnTime = 0;
        }

        BaseObject* collisionObject = PATH->checkCollision(*PLAYER);
        if ((collisionObject != nullptr)&&!collisionObject->reg) {
            PLAYER->health -= 12;
			collisionObject->reg = true;
            std::cout << "Player Health: " << PLAYER->health << std::endl;
			string ToPlay = "hurt" + std::to_string(rand() % 4 + 1);
            SFX->PlaySoundEffect(ToPlay);
        }

        if (PLAYER->health <= 0) {
            gameover = true;
        }
        if (jump) {
			string ToPlay = "jump" + std::to_string(rand() % 2 + 1);
			SFX->PlaySoundEffect(ToPlay);
        }

        // Render ground and other game elements
        PATH->renderGround(SDL->GetRenderer(), groundTexture, speed);
        PATH->renderPath(SDL->GetRenderer());
        PLAYER->render(SDL->GetRenderer(), deltaTime, 1.5f);
        
        SDL_RenderPresent(SDL->GetRenderer());

        int delayTime = 16 - deltaTime;
        if (delayTime < 0) {
            delayTime = 0;
        }
        SDL_Delay(delayTime);
        previousTime = currentTime;
        gameTime += deltaTime;
    }
}
