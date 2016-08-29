#include "MyClock.h"
#include <string>

MyClock::MyClock()
{
	text.setCharacterSize(24);
	text.setColor(sf::Color::Red);
}

void MyClock::addTime(int hours, int min, int sec, int milli)
{
	milliseconds += milli;
	while (milliseconds >= 1000)
	{
		seconds++;
		milliseconds -= 1000;
	}

	seconds += sec;
	while (seconds >= 60)
	{
		minutes++;
		seconds -= 60;
	}

	minutes += min;
	while (minutes >= 60)
	{
		this->hours++;
		minutes -= 60;
	}

	this->hours += hours;

	setString();
}

void MyClock::setString()
{
	text.setString(
		std::to_string(hours) + ":" +
		std::to_string(minutes) + ":" +
		std::to_string(seconds) + ":" +
		std::to_string(milliseconds));
}

void MyClock::reset()
{
	hours = 0;
	minutes = 0;
	seconds = 0;
	milliseconds = 0;

	setString();
}

void MyClock::setFont(sf::Font& font)
{
	text.setFont(font);
}

void MyClock::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(text, states.transform *= getTransform());
}