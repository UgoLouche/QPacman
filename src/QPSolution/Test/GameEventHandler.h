#pragma once

#include "EventHandler.h"

//Forward Declaration
class GameObject;

enum KeyValues
{
	Z = 0,
	Q = 1,
	S = 2,
	D = 3
};

class GameEventHandler : public ProtoEng::EventHandler
{
public:
	GameEventHandler();
	~GameEventHandler();

	void linkParent(GameObject* parent);

	bool isKeyPressed(int id);

private:
	GameObject* parent_game;
	
	virtual void handleEvent(const sf::Event& ev) override;

	bool keys[4]; //0->'Z', 1->'Q', 2->'S', 3->'D'
};