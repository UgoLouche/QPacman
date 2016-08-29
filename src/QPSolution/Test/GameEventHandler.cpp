#include "GameEventHandler.h"
#include "GameObject.h"

GameEventHandler::GameEventHandler() : parent_game(NULL)
{
	for (int i = 0; i < 4; i++)
		keys[i] = false;
}

GameEventHandler::~GameEventHandler()
{
}

void GameEventHandler::linkParent(GameObject * parent)
{
	parent_game = parent;
}

bool GameEventHandler::isKeyPressed(int id)
{
	if (id < 4 && id >= 0)
		return keys[id];
	else
		return false;
}

void GameEventHandler::handleEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::Closed:
		parent_game->getWindow()->close();
		break;

	case sf::Event::KeyPressed: //Awful code is awful
		switch (ev.key.code)
		{
		case sf::Keyboard::Z:
			keys[KeyValues::Z] = true;
			break;
		case sf::Keyboard::Q:
			keys[KeyValues::Q] = true;
			break;
		case sf::Keyboard::S:
			keys[KeyValues::S] = true;
			break;
		case sf::Keyboard::D:
			keys[KeyValues::D] = true;
			break;
		default:
			break;
		}
		break;

	case sf::Event::KeyReleased:
		switch (ev.key.code)
		{
		case sf::Keyboard::Z:
			keys[KeyValues::Z] = false;
			break;
		case sf::Keyboard::Q:
			keys[KeyValues::Q] = false;
			break;
		case sf::Keyboard::S:
			keys[KeyValues::S] = false;
			break;
		case sf::Keyboard::D:
			keys[KeyValues::D] = false;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}
