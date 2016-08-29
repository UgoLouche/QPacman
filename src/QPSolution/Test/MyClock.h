#pragma once

#include "SFML\Graphics.hpp"

class MyClock : public sf::Drawable, public sf::Transformable
{
public:
	MyClock();

	void addTime(int hours, int min, int sec, int milli);
	void reset();

	void setFont(sf::Font& font);

private:
	void setString();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Text text;

	int hours;
	int minutes;
	int seconds;
	int milliseconds;
};