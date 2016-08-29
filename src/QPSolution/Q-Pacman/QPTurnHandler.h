#pragma once

#include "TimedEvent.h"

#include "SFML\Graphics.hpp"

class QPacman;
class QPWorld;

class QPTurnHandler : public ProtoEng::TimedEvent
{
public:
	QPTurnHandler(sf::Time time = sf::seconds(1), bool recurrent = true);
	~QPTurnHandler();

	//Link
	void linkWorld(QPWorld* wld);
	void linkParent(QPacman* parent);

private:
	virtual void trigger_custom() override;
	virtual std::string custom_log_header() const override;

	QPacman* parent;
	QPWorld* world;
};