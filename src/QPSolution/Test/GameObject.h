#pragma once

#include "GameWorld.h"
#include "GameWindow.h"
#include "GameEventHandler.h"
#include "TestWorld.h"
#include "GameplayManager.h"
#include "MyClock.h"

enum LayerTypes
{
	GameEntity = 0,
	GameUI = 1
};


class GameObject : public  ProtoEng::GameplayManager //Store all game related stuff
{
public:
	GameObject();
	~GameObject();

	void initialize();
	void launch();

	ProtoEng::GameWindow* getWindow();
	GameEventHandler getHandler();

	void setBall(MyEntity* theBall);

private:
	//void preUpdate_custom() override;
	void newEvent_custom(const sf::Event& ev) override;
	void gameplayUpdate_custom() override;
	//void postUpdate_custom() override;

	MyEntity* theBall;

	float lenght;
	float width;

	TestWorld world;
	ProtoEng::GameWindow win;
	GameEventHandler handler;
	sf::Font font;
	sf::Text* text;

	int frameCount;

	MyClock* clock;
};