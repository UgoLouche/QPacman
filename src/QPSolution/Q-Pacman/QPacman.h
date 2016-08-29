#pragma once

#include "QPEventHandler.h"
#include "QPWorld.h"
#include "QPTurnHandler.h"
#include "QPSpriteFactory.h"
#include "QPLogger.h"
#include "QPInput.h"
#include "QPUIManager.h"
#include "QPRandomManager.h"

#include "GameplayManager.h"
#include "GameWindow.h"

#include "SFML\Graphics.hpp"

#include <cstdint>


 class QPacman : public ProtoEng::GameplayManager
{
public:
	//Constructor / Destructor
	QPacman();
	~QPacman();

	//Initialize and launch game / close
	void launch();
	void quit();

	//Getter
	const ProtoEng::GameWindow& getWindow() const;
	const QPLogger& getLogger() const;
	const QPSpriteFactory& getSpriteFactory() const;
	const QPInput& getInput() const;
	const QuantumEntity& getPlayer() const;

	//Input Notifications
	void inputEvent(uint16_t keyFlag);

	//Entity Effects
	void changePlayerHealth(float delta);
	void changePlayerScore(float delta);
	void playerGoSuper(sf::Vector2i pos);

	//Randum Number
	void setRandomBounds(int min, int max);
	int nextRndInt() const;

	//Pause / GameOver
	void pause();
	bool pauseStatus() const;
	void gameOver(bool isOver);
	void restart();


private:
	//Init / start
	void setBoard();
	void initialize();
	void start();

	//Overrides
	virtual void preUpdate_custom() override;
	virtual void newEvent_custom(const sf::Event& ev) override;
	//virtual void gameplayUpdate_custom() override;

	virtual std::string custom_log_header() const override;


	//Attributes
	//Inputs
	QPInput inputState;
	bool isPaused;
	bool isGameOver;

	//Game Related Attributes
	ProtoEng::GameWindow win;
	QPWorld world;

	//Handler / Manager / Factories
	QPEventHandler eventHandler;
	QPSpriteFactory spriteFactory;

	//Logger
	QPLogger logger;

	//UI
	QPUIManager uiManager;

	//Random Generator
	QPRandomManager rndManager;

	//Player stats are stored here
	float playerHealth;
	float playerScore;


};