#include "QPTurnHandler.h"

#include "ClassicEntity.h"
#include "QPWorld.h"
#include "QPacman.h"
#include "QuantumEntity.h"

#include <list>

QPTurnHandler::QPTurnHandler(sf::Time time, bool recurrent)
	: ProtoEng::TimedEvent(time, recurrent), parent(NULL), world(NULL)
{
}

QPTurnHandler::~QPTurnHandler()
{
}

void QPTurnHandler::linkWorld(QPWorld * wld)
{
	world = wld;
}

void QPTurnHandler::linkParent(QPacman * parent)
{
	this->parent = parent;
}

//Player Act First
void QPTurnHandler::trigger_custom()
{
	if (!parent->pauseStatus())
	{
		std::list<ClassicEntity*>::iterator it;

		world->getPlayer()->act(getBaseTime());

		for (it = world->getEntities().begin(); it != world->getEntities().end(); ++it)
		{
			(*it)->act(getBaseTime());
			(*it)->collision();
		}
	}
	
	//reset input
	parent->inputEvent(QPInput::KEY_0);
}

std::string QPTurnHandler::custom_log_header() const
{
	return "::TurnHandler::";
}
