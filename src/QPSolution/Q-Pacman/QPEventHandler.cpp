#include "QPEventHandler.h"
#include "QPacman.h"

QPEventHandler::QPEventHandler()
	: parent(NULL)
{
}

QPEventHandler::~QPEventHandler()
{
}

void QPEventHandler::linkParent(QPacman* parent)
{
	this->parent = parent;
}

void QPEventHandler::handleEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::Closed:
		parent->quit();
		break;

	case sf::Event::KeyPressed:
		keyEvent(ev);
		break;

	default:
		//infoLog("Event unknown or un-handled");
		break;
	}
}

std::string QPEventHandler::custom_log_header() const
{
	return "::QPEventHandler::";
}

void QPEventHandler::keyEvent(const sf::Event & ev) const
{
	//Catch Pause
	if (ev.key.code == sf::Keyboard::P) parent->pause();
	else if (ev.key.code == sf::Keyboard::N) parent->restart();
	else
	{
		uint16_t keyFlag = getKey(ev);

		//Forward only relevant keys
		if (keyFlag != 0xFFFF) parent->inputEvent(keyFlag);
	}
}

uint16_t QPEventHandler::getKey(const sf::Event & ev) const
{
	switch (ev.key.code)
	{
	case sf::Keyboard::Numpad0:
		return QPInput::KEY_0;

	case sf::Keyboard::Numpad1:
		return QPInput::KEY_1;

	case sf::Keyboard::Numpad2:
		return QPInput::KEY_2;

	case sf::Keyboard::Numpad3:
		return QPInput::KEY_3;

	case sf::Keyboard::Numpad4:
		return QPInput::KEY_4;

	case sf::Keyboard::Numpad5:
		return QPInput::KEY_5;

	case sf::Keyboard::Numpad6:
		return QPInput::KEY_6;

	case sf::Keyboard::Numpad7:
		return QPInput::KEY_7;

	case sf::Keyboard::Numpad8:
		return QPInput::KEY_8;

	case sf::Keyboard::Numpad9:
		return QPInput::KEY_9;

	default:
		return 0xFFFF;
	}
}
