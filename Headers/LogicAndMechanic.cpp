#include "LogicAndMechanic.h"


void gameLoop(SDL_Manager* SDL, Player* PLAYER, PathManager* PATH, SDL_Event* event, std::vector<Layer>& backgroundLayers, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI) {
    bool gameover = false;
    bool quit = false;
    int intervalSpawn = 1200;
    int spawnTime = 0;
    int gameTime = 0;
    int previousTime = SDL_GetTicks();
    int speed = 5;
    int SkillCooldown = 20000;
	int SkillCooldownTime = 0;
    int SkillTime = 3000;
	int SkillStart = 0;
	bool usingSkill = false;
    bool musicStarted = false;
    int buffer = 0;

    int distupdt = 0;
    int scoreupdt = 0;
    uint64_t Score = 0;
    uint64_t Dist = 0;
    
    SFX->StopMusic();
    SDL_Texture* groundTexture = LoadTexture(SDL->GetRenderer(), GROUNDSPRITEPATH);

    while (!quit && !gameover) {
        bool PlayingMusic = Mix_PlayingMusic();
        int currentTime = SDL_GetTicks();
        int deltaTime = currentTime - previousTime;
        int estTime = 0;

        while (SDL_PollEvent(event)) {
            if (event->type == SDL_QUIT) {
                quit = true;
            }
        }

        if (SDL_GetTicks() - estTime >= 100) {
            if (!PlayingMusic && !musicStarted) {
                srand(SDL_GetTicks());
                int toPlay = rand()%SFX->GetMusicCount();
                SFX->PlayMusic(to_string(toPlay),0);
                std::cout << "Play music" << std::endl;
                musicStarted = true; estTime = SDL_GetTicks();
            }
            else if (!PlayingMusic && musicStarted) {
                musicStarted = false;
            }
        }
        SDL_RenderClear(SDL->GetRenderer());

        RenderParallaxBackground(SDL->GetRenderer(), backgroundLayers, 800, 425, deltaTime, speed);
        
        bool isJumping = SDL->IsKeyDown(SDL_SCANCODE_Z);
		bool isFastlanding = SDL->IsKeyDown(SDL_SCANCODE_X);
        float gravity = 0.5f;
        float jumpStrength = 10.0f;
        int groundLevel = 370;
        bool jump = PLAYER->update(isJumping,isFastlanding, gravity, jumpStrength, groundLevel);

        if (SkillCooldownTime < 0) {
			SkillCooldownTime = 0;
        }

		if (SDL->IsKeyDown(SDL_SCANCODE_C)) {
			if (SkillCooldownTime == 0) {
                SkillStart = 0;
                SkillCooldownTime = SkillCooldown;
				usingSkill = true;
                PLAYER->health += 12;
			}
		}
        float displaySkillBar;
        if (usingSkill) {
            SkillStart += deltaTime;
            if (SkillStart >= SkillTime) {
                usingSkill = false;
                SkillStart = 0;
				PLAYER->setAlpha(255);
            }
            if (SkillTime % 500 == 0) {
                int flicker = DRNG(100, 255);
                PLAYER->setAlpha(flicker);
            }
            displaySkillBar = static_cast<float>(SkillTime - SkillStart) / static_cast<float>(SkillTime);
        }

        float displayHealthBar;
		
        if (!usingSkill) {
            displaySkillBar = static_cast<float>(SkillCooldown - SkillCooldownTime) / SkillCooldown;
			PLAYER->setAlpha(255);
        }
        if (gameTime >= 3000) {
            speed += 1;
            gameTime = 0;
			speed = SDL_clamp(speed, 5, 20);
        }
		TEXT->RenderText("Default", "Speed: " + std::to_string(speed), 10, 50, { 255, 0, 0, 255 }, 30);
		
        PATH->UPDATE(SDL->GetRenderer(), speed);
        spawnTime += deltaTime;

        if (spawnTime >= intervalSpawn) {
            int randomIndex = DRNG(0, obstacle.size() - 1);
            PATH->addNewObject(800, groundLevel, obstacle[randomIndex].size.first, obstacle[randomIndex].size.second, obstacle[randomIndex].spritepath, SDL->GetRenderer());
            spawnTime = 0;
        }



        BaseObject* collisionObject = PATH->checkCollision(*PLAYER);
        if ((collisionObject != nullptr)&&!collisionObject->reg&&!usingSkill) {
			collisionObject->reg = true;
            std::cout << "Player Health: " << PLAYER->health << std::endl;
			string ToPlay = "hurt" + std::to_string(rand() % 4 + 1);
            SFX->PlaySoundEffect(ToPlay);
            Score -= 100;
            buffer += 12;
        }

		if (buffer > 0) {
			buffer -= deltaTime;
			if (buffer <= 0) {
				PLAYER->health -= 10;
				buffer = 0;
			}
		}

		PLAYER->health = SDL_clamp(PLAYER->health, 0, 100);
        if (PLAYER->health <= 0) {
            gameover = true;
        }

        if (jump) {
			string ToPlay = "jump" + std::to_string(rand() % 2 + 1);
			SFX->PlaySoundEffect(ToPlay);
        }

		if (scoreupdt >= 100) {
            srand(SDL_GetTicks());
            Score += static_cast<int>(speed * (rand() * 2 / 1000));
			scoreupdt = 0;
            Dist += speed;
			distupdt = 0;
		}
  
        PATH->renderPath(SDL->GetRenderer());
        PLAYER->render(SDL->GetRenderer(), deltaTime, 1.5f);
		GUI->render(SDL->GetRenderer(), static_cast<float>(PLAYER->health) / 100, displaySkillBar);
        TEXT->RenderText("Bold", std::to_string(Score), 30, 500, { 255, 0, 0, 255 }, 30);
		TEXT->RenderText("Default", std::to_string(Dist), 390, 30, { 255, 0, 0, 255 }, 30);
        SDL_RenderPresent(SDL->GetRenderer());

        int delayTime = 16 - deltaTime;
        if (delayTime < 0) {
            delayTime = 0;
        }
        SDL_Delay(delayTime);
        previousTime = currentTime;
        gameTime += deltaTime;
		scoreupdt += deltaTime;
		distupdt += deltaTime;
		SkillCooldownTime -= deltaTime;
		
    }
}

int DRNG(int bot, int top) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(bot, top);
    return dist(rng);
}

