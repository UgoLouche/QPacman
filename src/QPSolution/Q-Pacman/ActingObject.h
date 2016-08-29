#pragma once

#include "LoggedObject.h"

#include "SFML\Graphics.hpp"

class ActingObject : virtual public ProtoEng::LoggedObject
{
public:
	ActingObject();
	virtual ~ActingObject();

	//Called everytime the entity "Act"
	//UntilNextAction: Time frame to perform animation
	void act(sf::Time untilNextAction);

	//Called before each graphic update, allow to keep track of time
	void notifyGraphicUpdate(sf::Time deltaTime);

protected:
	//Return the ratio (over a gameplay step) of how much time has passed
	//since the last gameplay update
	float getActionTimeRatio() const;

private:
	virtual void notifyGraphicUpdate_custom(sf::Time deltaTime);
	virtual void act_custom() = 0;

	//Ad hoc attributes
	sf::Time untilNextAction; //Remaining time before the next action
	sf::Time actionCooldown;     //Total time between this action and the next
};