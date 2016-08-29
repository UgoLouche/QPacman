#include "QPUIManager.h"

#include "QPInput.h"

#include "const.h"

#include "SFML\Graphics.hpp"

QPUIManager::QPUIManager() : 
	font(),
	fps_counter(NULL),
	score(NULL),
	health(NULL),
	gameMessage(NULL),
	gameMessage_subtext(NULL),
	healthBar(NULL),
	keyButtons(10, NULL)
{
}

QPUIManager::~QPUIManager()
{
}

void QPUIManager::init()
{
	if (!font.loadFromFile(FONT_FILE)) warnLog("Cannot Load Font");
}

void QPUIManager::linkFps_counter(sf::Text * fps_counter)
{
	this->fps_counter = fps_counter;
}

void QPUIManager::linkScore(sf::Text * score)
{
	this->score = score;
}

void QPUIManager::linkHealth(sf::Text * health)
{
	this->health = health;
}

void QPUIManager::linkHealthBar(sf::RectangleShape * healthBar)
{
	this->healthBar = healthBar;
}

void QPUIManager::linkKeyButtons(std::vector<sf::Sprite*> buttons)
{
	keyButtons = buttons;
}

void QPUIManager::linkGameMessage(sf::Text * main, sf::Text * subtext)
{
	gameMessage = main;
	gameMessage_subtext = subtext;

	gameMessage->setString("");
	gameMessage_subtext->setString("");
}

void QPUIManager::notifyNewFrame(sf::Time deltaTime)
{
	//Catch NULL value
	if (fps_counter == NULL)
	{
		warnLog("New Frame notyfied but no fps counter");
		return;
	}

	int fps = (int)(1 / deltaTime.asSeconds());

	if (fps_counter != NULL)
		fps_counter->setString(FPS_TEXT + std::to_string(fps));
}

void QPUIManager::scoreUpdate(float newScore)
{
	//Catch NULL value
	if (score == NULL)
	{
		warnLog("score Update but no score field");
		return;
	}

	//Only show a int version of the score
	std::string score_str = std::to_string((int)newScore);
	std::string finalString = std::string(SCORE_SIZE, '0');

	for (int i = 1; i <= SCORE_SIZE; ++i)
	{
		if (i <= score_str.size())
			finalString[SCORE_SIZE - i] = score_str[score_str.size() - i];
	}

	score->setString(SCORE_TEXT + finalString);
}

void QPUIManager::healthUpdate(float newHealth)
{
	if (health == NULL || healthBar == NULL)
	{
		warnLog("health update but one or more UI component are missing for health");
		return;
	}

	if (newHealth < 100)
	{
		if (newHealth < 10) health->setString("00" + std::to_string((int)newHealth));
		else health->setString("0" + std::to_string((int)newHealth));
	}
	else health->setString(std::to_string((int)newHealth));

	healthBar->setSize(sf::Vector2f(
		( newHealth / MAX_HEALTH )*HEALTH_WIDTH, 
		HEALTH_HEIGHT
	));
}

void QPUIManager::inputNotify(uint16_t keyFlag)
{
	if ((keyFlag == QPInput::KEY_0)) //Reset all
	{
		for (int i = 1; i <= 9; ++i) updateButton(i, false);
	}
	else
	{
		if ((keyFlag & QPInput::KEY_1) > 0) updateButton(1, true);
		if ((keyFlag & QPInput::KEY_2) > 0) updateButton(2, true);
		if ((keyFlag & QPInput::KEY_3) > 0) updateButton(3, true);
		if ((keyFlag & QPInput::KEY_4) > 0) updateButton(4, true);
		if ((keyFlag & QPInput::KEY_5) > 0) updateButton(5, true);
		if ((keyFlag & QPInput::KEY_6) > 0) updateButton(6, true);
		if ((keyFlag & QPInput::KEY_7) > 0) updateButton(7, true);
		if ((keyFlag & QPInput::KEY_8) > 0) updateButton(8, true);
		if ((keyFlag & QPInput::KEY_9) > 0) updateButton(9, true);
	}
}

void QPUIManager::pause(bool isPause)
{
	if (isPause)
	{
		gameMessage->setString(PAUSE_TEXT);
		gameMessage_subtext->setString(PAUSE_SUBTEXT);

		centerMessages();
	}
	else
	{
		gameMessage->setString("");
		gameMessage_subtext->setString("");
	}
}

void QPUIManager::gameOver(bool isGameOver)
{
	if (isGameOver)
	{
		gameMessage->setString(GAMEOVER_TEXT);
		gameMessage_subtext->setString(GAMEOVER_SUBTEXT);

		centerMessages();
	}
	else
	{
		gameMessage->setString("");
		gameMessage_subtext->setString("");
	}
}

const sf::Font & QPUIManager::getFont() const
{
	return font;
}

std::string QPUIManager::custom_log_header() const
{
	return "::QPUIManager::";
}

void QPUIManager::updateButton(size_t index, bool isPressed)
{
	if (keyButtons[index] == NULL) //Catch NULL values
	{
		warnLog("Button Event but no Sprite linked.");
		return;
	}

	if (!isPressed)
	{
		keyButtons[index]->setTextureRect(sf::IntRect(
			0,
			(int)index * UI_TEX_SIZE,
			UI_TEX_SIZE,
			UI_TEX_SIZE
		));
	}
	else
	{
		//First reset all buttons
		for (int i = 0; i < 9; i++) updateButton(i, false);

		keyButtons[index]->setTextureRect(sf::IntRect(
			UI_TEX_SIZE,
			(int)index * UI_TEX_SIZE,
			UI_TEX_SIZE,
			UI_TEX_SIZE
		));
	}
}

void QPUIManager::centerMessages()
{
	sf::FloatRect bounds;

	bounds = gameMessage->getLocalBounds();
	gameMessage->setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

	bounds = gameMessage_subtext->getLocalBounds();
	gameMessage_subtext->setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}
