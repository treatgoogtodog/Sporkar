#include "LogicAndMechanic.h"


GAMESTATE gameLoop(SDL_Manager* SDL, Player* PLAYER, PathManager* PATH, SDL_Event* event, std::vector<Layer>& backgroundLayers, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI, bool& resetFlag) {
	bool gameover = false;
	bool quit = false;
	static int intervalSpawn = 1200;
	static int spawnTime = 0;
	static int gameTime = 0;
	static int previousTime = SDL_GetTicks();
	static int SkillCooldown = 20000;
	static int SkillTime = 3000;
	static int SkillStart = 0;
	static int speed = 5;
	static int SkillCooldownTime = 0;
	static bool usingSkill = false;
	static bool musicStarted = false;
	static int buffer = 0;
	static int distupdt = 0;
	static int scoreupdt = 0;
	static uint64_t Score = 0;
	static uint64_t Dist = 0;
	static int failCount = 0;
	static int MaxFail = 5;
	static PowerUpEffect CurrentEffect = NONE;
	static bool speedOverDrive = false;
	static int SpeedOverDriveTime = 10000;
	static int SpeedOverDriveStart = 0;
	static int SpeedWindUp = 3000;
	static int NukeDelay = 5000;
	static int NukeTimer = -1;

	if (resetFlag) {
		intervalSpawn = 1200;
		spawnTime = 0;
		gameTime = 0;
		SkillCooldown = 20000;
		SkillTime = 3000;
		SkillStart = 0;
		speed = 5;
		SkillCooldownTime = 0;
		usingSkill = false;
		musicStarted = false;
		buffer = 0;
		PLAYER->health = 100;
		distupdt = 0;
		scoreupdt = 0;
		Score = 0;
		Dist = 0;
		failCount = 0;
		CurrentEffect = NONE;
		speedOverDrive = false;
		PATH->cleanUp();
		resetFlag = false;
	}

	SDL_Texture* groundTexture = LoadTexture(SDL->GetRenderer(), GROUNDSPRITEPATH);

	while (!quit && !gameover) {
		bool PlayingMusic = Mix_PlayingMusic();
		int currentTime = SDL_GetTicks();
		int deltaTime = currentTime - previousTime;
		int estTime = 0;

		while (SDL_PollEvent(event)) {
			if (event->type == SDL_QUIT) {
				quit = true;
				return EXIT;
			}
		}

		if (SDL_GetTicks() - estTime >= 100) {
			if (!PlayingMusic && !musicStarted) {
				srand(SDL_GetTicks());
				int toPlay = rand() % SFX->GetMusicCount();
				SFX->PlayMusic(to_string(toPlay), 0);
				std::cout << "Play music" << std::endl;
				musicStarted = true; estTime = SDL_GetTicks();
			}
			else if (!PlayingMusic && musicStarted) {
				musicStarted = false;
			}
		}
		SDL_RenderClear(SDL->GetRenderer());

		RenderParallaxBackground(SDL->GetRenderer(), backgroundLayers, 800, 425, deltaTime, speed);

		if (SDL->IsKeyDown(SDL_SCANCODE_P)) {
			return PAUSE;
		}

		bool isJumping = SDL->IsKeyDown(SDL_SCANCODE_Z);
		bool isFastlanding = SDL->IsKeyDown(SDL_SCANCODE_X);
		float gravity = 0.5f;
		float jumpStrength = 12.0f;
		int groundLevel = 370;
		bool jump = PLAYER->update(isJumping, isFastlanding, gravity, jumpStrength, groundLevel);

		if (SkillCooldownTime < 0) {
			SkillCooldownTime = 0;
			
		}

		if (SDL->IsKeyDown(SDL_SCANCODE_C)) {
			if ((SkillCooldownTime == 0) && !usingSkill) {
				SkillStart = 0;
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
				SkillCooldownTime = SkillCooldown;
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
		if (!speedOverDrive) {
			PLAYER->setColorMod(255, 255, 255);
			if (gameTime >= 3000) {
				speed += 1;
				gameTime = 0;
				speed = SDL_clamp(speed, 5, 20);
			}
		}

		if (speedOverDrive) {
			SpeedOverDriveStart += deltaTime;
			PLAYER->setColorMod(52, 189, 255);
			if (SpeedOverDriveStart <= SpeedWindUp) {
				speed = 1; 
				std::string W = "WindUp";
				GUI->RenderSingle(SDL->GetRenderer(), W);
			}
			else {
				speed = 35;
				if (SpeedOverDriveStart >= SpeedWindUp + SpeedOverDriveTime) {
					speedOverDrive = false;
					SpeedOverDriveStart = 0;
					speed = SDL_clamp(speed, 5, 20);
					CurrentEffect = NONE;
				}
			}
		}
		TEXT->RenderText("Default", "Speed: " + std::to_string(speed), 10, 50, { 255, 0, 0, 255 }, 30);

		PATH->UPDATE(SDL->GetRenderer(), speed);
		spawnTime += deltaTime;

		if (spawnTime >= intervalSpawn) {
			int roll = DRNG(1, 1000);
			if (roll > 950) {
				int randomIndex = DRNG(0, powerup.size() - 1);
				PATH->addNewPowerUp(800, groundLevel - 80, powerup[randomIndex].size.first, powerup[randomIndex].size.second, powerup[randomIndex].spritepath, SDL->GetRenderer(), powerup[randomIndex].Effect);
				failCount = 0;
			}
			else {
				int randomIndex = DRNG(0, obstacle.size() - 1);
				int spany = (obstacle[randomIndex].type == 0) ? groundLevel - 100 : groundLevel;
				PATH->addNewObject(800, spany, obstacle[randomIndex].size.first, obstacle[randomIndex].size.second, obstacle[randomIndex].spritepath, SDL->GetRenderer(), obstacle[randomIndex].type);	
				failCount++;
			}
			spawnTime = DRNG(0, 700);
		}

		if (speed <= 20 && speed > 5) {
			BaseObject* collisionObject = PATH->checkCollision(*PLAYER);
			if ((collisionObject != nullptr) && !collisionObject->reg && !usingSkill) {
				collisionObject->reg = true;
				std::cout << "Player Health: " << PLAYER->health << std::endl;
				string ToPlay = "hurt" + std::to_string(rand() % 4 + 1);
				SFX->PlaySoundEffect(ToPlay);
				Score -= 100;
				PLAYER->health -= 12 + speed / 10;
				speed = SDL_clamp(speed - 5, 5, 20);
			}
		}
		PowerUp* collisionPowerUp = PATH->checkPowerUpCollision(*PLAYER);
		if (collisionPowerUp != nullptr && !collisionPowerUp->reg) {
			collisionPowerUp->reg = true;
			string ToPlay = "pickup" + std::to_string(rand() % 2 + 1);
			SFX->PlaySoundEffect(ToPlay);
			CurrentEffect = collisionPowerUp->getEffect();
			switch (CurrentEffect) {
			case HYPER: {
				speedOverDrive = true;
				speed = 0;
				SFX->PlaySoundEffect("hyper" + to_string(DRNG(1, 2)));
				break;
			}
			case NUKE: {
				PATH->cleanUp();
				break;
			}
			case GAMBLE: {
				int roll = DRNG(1, 100);
				if (roll > 50) {
					PLAYER->health += 20;
					Score = Score * 2;
					speed += 5;
					speed = SDL_clamp(speed, 5, 20);
				}
				else {
					PLAYER->health -= 20;
					Score = Score / 2;
					speed = SDL_clamp(speed, 5, 20);
				}
				break;
			}
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
			PLAYER->render(SDL->GetRenderer(), (deltaTime*speed)/12, 1.5f);
			GUI->render(SDL->GetRenderer(), static_cast<float>(PLAYER->health) / 100, displaySkillBar);
			TEXT->RenderText("Bold", std::to_string(Score), 30, 500, { 255, 0, 0, 255 }, 30);
			TEXT->RenderText("Default", std::to_string(Dist), 390, 30, { 255, 0, 0, 255 }, 30);
			TEXT->RenderText("Default", std::to_string(speed), 525, 30, { 255, 0, 0, 255 }, 20);

			if (speedOverDrive) {
				if (SpeedOverDriveStart <= SpeedWindUp) {
					speed = 1;
					std::string W = "WindUp";
					GUI->RenderSingle(SDL->GetRenderer(), W);
				}
			}

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
		if (gameover) {
			WriteScore(".sav", Score);
			return LOSS;
		}
		SFX->StopMusic();
		return MENU;
}

int DRNG(int bot, int top) {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dist(bot, top);
	return dist(rng);
}

GAMESTATE Menu(SDL_Manager* SDL, SDL_Event* event, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI, GAMELOOPDATA& gamedata) {
	SFX->StopMusic();
	int previousTime = 0;
	int currentTime = SDL_GetTicks();
	int deltaTime = 0;
	int elasp = 0;
	bool quit = false;
	bool openscoreboard = false;
	SDL_Texture* backgroundTexture = LoadTexture(SDL->GetRenderer(), "Sprite\\GUI\\Splash.png");
	SDL_Texture* buttonTexture = LoadTexture(SDL->GetRenderer(), "Sprite\\GUI\\buttons.png");
	Button START(SDL->GetRenderer(), SFX, buttonTexture, startButton, 494, 349, 272, 64);
	Button HSCORE(SDL->GetRenderer(), SFX, buttonTexture, hscoreButton, 494, 424, 273, 65);
	Button QUIT(SDL->GetRenderer(), SFX, buttonTexture, quitButton, 494, 496, 274, 66);
	Button MUTE(SDL->GetRenderer(), SFX, buttonTexture, quitButton, 0, 0, 274, 66);
	Slider MusicSlider(SDL->GetRenderer(), "Sprite\\GUI\\sound_slider.png", "Sprite\\GUI\\sound_slider_t.png", 96, 559, 224, 16);
	Slider SFXSlider(SDL->GetRenderer(), "Sprite\\GUI\\sound_slider.png", "Sprite\\GUI\\sound_slider_t.png", 96, 500, 224, 16);
	MusicSlider.setValue(static_cast<float>(static_cast<float>(SFX->GetVolume().first) / static_cast<float>(MIX_MAX_VOLUME)));
	SFXSlider.setValue(static_cast<float>(static_cast<float>(SFX->GetVolume().second) / static_cast<float>(MIX_MAX_VOLUME)));
	while (!quit) {

		while (SDL_PollEvent(event)) {
			if (event->type == SDL_QUIT) {
				return EXIT;
			}
		}

		bool playingMusic = Mix_PlayingMusic();
		if (!playingMusic) {
			int toPlay = DRNG(SFX->GetCustomCount() + 1, SFX->GetMusicCount());
			SFX->PlayMusic(to_string(toPlay), 0);
		}
		SFX->SetMusicVolume(static_cast<float>(MIX_MAX_VOLUME) * MusicSlider.getValue());
		for (int i = 0; i < 15; i++) {
			Mix_Volume(i, static_cast<float>(MIX_MAX_VOLUME) * SFXSlider.getValue());
		}

		SDL_RenderClear(SDL->GetRenderer());

		int mouseX, mouseY;
		bool clicked = SDL_GetMouseState(&mouseX, &mouseY) == SDL_BUTTON(1);
		SDL_RenderCopy(SDL->GetRenderer(), backgroundTexture, nullptr, nullptr);
		START.update(mouseX, mouseY, deltaTime, clicked);
		START.render(SDL->GetRenderer());
		HSCORE.update(mouseX, mouseY, deltaTime, clicked);
		HSCORE.render(SDL->GetRenderer());
		QUIT.update(mouseX, mouseY, deltaTime, clicked);
		QUIT.render(SDL->GetRenderer());
		MusicSlider.update(mouseX, mouseY, clicked);
		MusicSlider.render(SDL->GetRenderer());
		SFXSlider.update(mouseX, mouseY, clicked);
		SFXSlider.render(SDL->GetRenderer());

		if (openscoreboard) {
			ScoreBoard(gamedata, ".sav");
		}

		SDL_RenderPresent(SDL->GetRenderer());
		currentTime = SDL_GetTicks();
		SDL_Delay(16);
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		if (START.isClicked(mouseX, mouseY, clicked)) {
			SDL_Log("START GAME WITH PRESET");
			int toPlay = DRNG(1, voicelinefx.size());
			SFX->PlaySoundEffect("voice0" + std::to_string(toPlay));
			SDL_Delay(2000);
			gamedata.resetFlag = true;
			return GAME;
		}
		if (QUIT.isClicked(mouseX, mouseY, clicked)) {
			return EXIT;
		}
		if (HSCORE.isClicked(mouseX, mouseY, clicked)) {
			if (elasp >= 100) {
				elasp = 0;
				openscoreboard = !openscoreboard;
			}
			else {
				elasp += deltaTime;
			}

		}

	}
	return EXIT;
}

GAMESTATE GamePause(SDL_Manager* SDL, SDL_Event* event, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI, GAMELOOPDATA& gamedata) {
	int popupWidth = 400;
	int popupHeight = 300;
	int screenWidth = SDL->GetWidth();
	int screenHeight = SDL->GetHeight();

	int popupX = screenWidth + 100;
	int popupY = (screenHeight - popupHeight) / 2;
	int targetX = (screenWidth - popupWidth);

	SDL_Texture* pauseTexture = LoadTexture(SDL->GetRenderer(), "Sprite/GUI/PauseMenu.png");
	SDL_Texture* pauseButtons = LoadTexture(SDL->GetRenderer(), "Sprite/GUI/Pausebuttons.png");
	Button resumeButton(SDL->GetRenderer(), SFX, pauseButtons, startButton, targetX + 100, popupY + 100, 200, 50);
	Button TitleButton(SDL->GetRenderer(), SFX, pauseButtons, hscoreButton, targetX + 100, popupY + 175, 200, 50);
	Button QuitButton(SDL->GetRenderer(), SFX, pauseButtons, quitButton, targetX + 100, popupY + 250, 200, 50);

	bool quit = false;
	bool paused = true;
	int animationSpeed = static_cast<int>(0.05f * abs(popupX - targetX));

	while (paused && !quit) {
		while (SDL_PollEvent(event)) {
			if (event->type == SDL_QUIT) {
				quit = true;
			}

			int mouseX, mouseY;
			bool click = SDL_GetMouseState(&mouseX, &mouseY) == SDL_BUTTON(1);

			if (resumeButton.isClicked(mouseX, mouseY, click)) {
				paused = false;
				gamedata.resetFlag = false;
				return GAME;
			}
			if (QuitButton.isClicked(mouseX, mouseY, click)) {
				return EXIT;
			}
			if (TitleButton.isClicked(mouseX, mouseY, click)) {
				gamedata.resetFlag = true;
				return MENU;
			}
		}

		if (popupX > targetX) {
			popupX -= animationSpeed;
			if (popupX < targetX) {
				popupX = targetX;
			}
			resumeButton.Move(popupX + 100, popupY + 100);
			QuitButton.Move(popupX + 100, popupY + 250);
			TitleButton.Move(popupX + 100, popupY + 175);
		}

		SDL_RenderClear(SDL->GetRenderer());
		RenderParallaxBackground(SDL->GetRenderer(), gamedata.backgroundLayers, 800, 425, 0, 0);
		gamedata.PATH->renderPath(SDL->GetRenderer());
		gamedata.PLAYER->DrawFrozen(SDL->GetRenderer(), 1.5f);
		gamedata.GUI->render(SDL->GetRenderer(), static_cast<float>(gamedata.PLAYER->health) / 100, 0.0f);


		SDL_Rect popupRect = { popupX, popupY, popupWidth, popupHeight };
		SDL_RenderCopy(SDL->GetRenderer(), pauseTexture, nullptr, &popupRect);

		int mouseX, mouseY;
		bool click = SDL_GetMouseState(&mouseX, &mouseY) == SDL_BUTTON(1);
		resumeButton.render(SDL->GetRenderer());
		resumeButton.update(mouseX, mouseY, 16, click);
		TitleButton.render(SDL->GetRenderer());
		TitleButton.update(mouseX, mouseY, 16, click);
		QuitButton.render(SDL->GetRenderer());
		QuitButton.update(mouseX, mouseY, 16, click);
		SDL_RenderPresent(SDL->GetRenderer());
		SDL_Delay(16);
	}
	SDL_DestroyTexture(pauseTexture);
	SDL_DestroyTexture(pauseButtons);
}


GAMESTATE GameOver(SDL_Manager* SDL, SDL_Event* event, SoundManager* SFX, TextHandler* TEXT, GUIhandler* GUI, GAMELOOPDATA& gamedata) {
	int popupWidth = 400;
	int popupHeight = 600;
	int screenWidth = SDL->GetWidth();
	int screenHeight = SDL->GetHeight();

	int popupX = -popupWidth;
	int popupY = 0;
	int targetX = 0;

	SDL_Texture* GameOverTexture = LoadTexture(SDL->GetRenderer(), "Sprite/GUI/gameover.png");
	SDL_Texture* pauseButtons = LoadTexture(SDL->GetRenderer(), "Sprite/GUI/Pausebuttons.png");
	Button TitleButton(SDL->GetRenderer(), SFX, pauseButtons, hscoreButton, targetX + 100, popupY + 175, 200, 50);
	Button QuitButton(SDL->GetRenderer(), SFX, pauseButtons, quitButton, targetX + 100, popupY + 250, 200, 50);

	bool quit = false;
	int animationSpeed = static_cast<int>(0.05f * abs(popupX - targetX));

	while (!quit) {
		while (SDL_PollEvent(event)) {
			if (event->type == SDL_QUIT) {
				quit = true;
			}

			int mouseX, mouseY;
			bool click = SDL_GetMouseState(&mouseX, &mouseY) == SDL_BUTTON(1);

			if (QuitButton.isClicked(mouseX, mouseY, click)) {
				return EXIT;
			}
			if (TitleButton.isClicked(mouseX, mouseY, click)) {
				return MENU;
			}
		}

		if (popupX < targetX) {
			popupX += animationSpeed;
			if (popupX > targetX) {
				popupX = targetX;
			}
			QuitButton.Move(popupX + 100, popupY + 250);
			TitleButton.Move(popupX + 100, popupY + 175);
		}

		SDL_RenderClear(SDL->GetRenderer());
		RenderParallaxBackground(SDL->GetRenderer(), gamedata.backgroundLayers, 800, 425, 0, 0);
		gamedata.PATH->renderPath(SDL->GetRenderer());
		gamedata.PLAYER->DrawFrozen(SDL->GetRenderer(), 1.5f);
		gamedata.GUI->render(SDL->GetRenderer(), static_cast<float>(gamedata.PLAYER->health) / 100, 0.0f);

		SDL_Rect popupRect = { popupX, popupY, popupWidth, popupHeight };
		SDL_RenderCopy(SDL->GetRenderer(), GameOverTexture, nullptr, &popupRect);

		int mouseX, mouseY;
		bool click = SDL_GetMouseState(&mouseX, &mouseY) == SDL_BUTTON(1);
		TitleButton.render(SDL->GetRenderer());
		TitleButton.update(mouseX, mouseY, 16, click);
		QuitButton.render(SDL->GetRenderer());
		QuitButton.update(mouseX, mouseY, 16, click);
		SDL_RenderPresent(SDL->GetRenderer());
		SDL_Delay(16);
	}
	SDL_DestroyTexture(GameOverTexture);
	SDL_DestroyTexture(pauseButtons);
}

void ScoreBoard(GAMELOOPDATA gamedata, string savPth) {
	SDL_Texture* scoreboardTexture = LoadTexture(gamedata.SDL->GetRenderer(), "Sprite/GUI/scoreboard.png");
	int w, h;
	SDL_QueryTexture(scoreboardTexture, nullptr, nullptr, &w, &h);
	SDL_Rect scoreboardRect = { 0, 0, w, h };
	SDL_RenderCopy(gamedata.SDL->GetRenderer(), scoreboardTexture, nullptr, &scoreboardRect);
	fstream file(savPth);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << savPth << std::endl;
		return;
	}
	vector<int> scoreboard;
	std::string line;
	int count = 0;
	while (getline(file, line) && count < 5) {
		int score = std::stoi(line);
		scoreboard.push_back(score);
		count++;
	}
	int renderidx = 0;
	for (auto& i : scoreboard) {
		if (renderidx >= 10) { break; }
		string scoreText = std::to_string(i);
		gamedata.TEXT->RenderText("Default", scoreText, 20, 20 + renderidx * 30, { 0, 0, 0, 255 }, 30);
		renderidx++;
	}
}

void WriteScore(const std::string& filePath, int newScore) {
	vector<int> scores;

	ifstream inputFile(filePath);
	if (inputFile.is_open()) {
		int score;
		while (inputFile >> score) {
			scores.push_back(score);
		}
		inputFile.close();
	}
	else {
		cerr << "Could not open file for reading. A new file will be created." << endl;
	}
	scores.push_back(newScore);

	sort(scores.begin(), scores.end(), greater<int>());

	ofstream outputFile(filePath, ios::trunc);
	if (outputFile.is_open()) {
		for (const int& score : scores) {
			outputFile << score << endl;
		}
		outputFile.close();
	}
	else {
		cerr << "Error: Could not open file for writing." << endl;
	}
}