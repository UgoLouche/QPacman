#pragma once

#include "LoggedObject.h"

#include "SFML\Graphics.hpp"

#include <vector>

class QPUIManager : public ProtoEng::LoggedObject
{
public:
	QPUIManager();
	~QPUIManager();

	void init();

	//Link
	void linkFps_counter(sf::Text* fps_counter);
	void linkScore(sf::Text* score);
	void linkHealth(sf::Text* health);
	void linkHealthBar(sf::RectangleShape* healthBar);
	void linkKeyButtons(std::vector<sf::Sprite*> buttons);
	void linkGameMessage(sf::Text* main, sf::Text* subtext);


	//Updates
	void notifyNewFrame(sf::Time deltaTime);
	void scoreUpdate(float newScore);
	void healthUpdate(float newHealth);
	void inputNotify(uint16_t keyFlag);
	void pause(bool isPause);
	void gameOver(bool isGameOver);

	//getter
	const sf::Font& getFont() const;

private:
	//Overrides
	virtual std::string custom_log_header() const override;

	void updateButton(size_t index, bool isPressed);
	void centerMessages();


	sf::Font font;

	sf::Text* fps_counter;
	sf::Text* score;
	sf::Text* health;

	sf::Text* gameMessage;
	sf::Text* gameMessage_subtext;

	sf::RectangleShape* healthBar;

	std::vector<sf::Sprite*> keyButtons;
};
