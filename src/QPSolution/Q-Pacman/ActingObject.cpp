#include "ActingObject.h"

ActingObject::ActingObject()
	: untilNextAction(sf::seconds(0)), actionCooldown(sf::seconds(1))
{
}

ActingObject::~ActingObject()
{
}

void ActingObject::act(sf::Time untilNextAction)
{
	actionCooldown = untilNextAction;
	this->untilNextAction = untilNextAction;

	act_custom();
}

void ActingObject::notifyGraphicUpdate(sf::Time deltaTime)
{
	untilNextAction -= deltaTime;

	notifyGraphicUpdate_custom(deltaTime);
}

float ActingObject::getActionTimeRatio() const
{
	if (actionCooldown == sf::seconds(0))
	{
		warnLog("getActionTimeRatio: divide by 0");
		return 0;
	}
	
	if (untilNextAction <= sf::seconds(0))
	{
		//infoLog("getActionTimeRatio: negative or null untilNextAction");
		return 0;
	}

	return untilNextAction / actionCooldown;
}

void ActingObject::notifyGraphicUpdate_custom(sf::Time deltaTime)
{
}
