#include "LogicAndMechanic.h"

void gameLoad(SDL_Manager* SDL, Player*& PLAYER) {
    const std::string playerTexturePath = PLAYERSPRITEPATH;
    const std::string playerTextureData = PLAYERSPRITESHEETDATA;
    PLAYER = new Player(100, 300, playerTexturePath, playerTextureData, SDL->GetRenderer(),1.2f);
}

void gameLoop(SDL_Manager* SDL, Player* PLAYER, PathManager* PATH, SDL_Event* event) {
    bool gameover = false;
    bool quit = false;
    int intervalSpawn = 1200;
    int spawnTime = 0;
    int gameTime = 0;
	int previousTime = SDL_GetTicks();
	int speed = 5;
    int bgOffset = 0;
	SDL_Texture* groundTexture = LoadTexture(SDL->GetRenderer(), GROUNDSPRITEPATH);
    while (!quit && !gameover) {
        int currentTime = SDL_GetTicks();
		int deltatime = currentTime - previousTime;
        while (SDL_PollEvent(event)) {
            if (event->type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_RenderClear(SDL->GetRenderer());
        bool isJumping = SDL->IsKeyDown(SDL_SCANCODE_SPACE);
        float gravity = 0.5f;
        float jumpStrength = 10.0f;
        int groundLevel = 300;
        PLAYER->update(isJumping, gravity, jumpStrength, groundLevel);
        if (gameTime >= 3000) {
            speed += 1;
            gameTime = 0;
			SDL_Log("Speed: %d", speed);
        }
        PATH->UPDATE(SDL->GetRenderer(), speed);
		spawnTime += deltatime;
		if (spawnTime >= intervalSpawn) {
			int randomIndex = rand() % obstacle.size();
			PATH->addNewObject(800, 300, obstacle[randomIndex].size.first, obstacle[randomIndex].size.second, obstacle[randomIndex].spritepath, SDL->GetRenderer());
			spawnTime = 0;
		}
        bgOffset += speed;
        BaseObject* collisionObject = PATH->checkCollision(*PLAYER);
        if (collisionObject != nullptr&& collisionObject->reg == false) {
			collisionObject->reg = true;
			PLAYER->health -= 33;
			SDL_Log("Player Health: %d", PLAYER->health);
        }
        if (PLAYER->health <= 0) { gameover = true; }

        PATH->renderGround(SDL->GetRenderer(),groundTexture, bgOffset);
        PATH->renderPath(SDL->GetRenderer());
        PLAYER->render(SDL->GetRenderer(), deltatime, 1.5f);
        SDL_RenderPresent(SDL->GetRenderer());
		
        int delaytime = 16 - deltatime;
		if (delaytime < 0) {delaytime = 0;}
        SDL_Delay(delaytime);
		previousTime = currentTime;
		gameTime += deltatime;
    }
}