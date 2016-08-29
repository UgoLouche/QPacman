#include "GameplayManager.h"

#include "TimedEvent.h"

using namespace ProtoEng;

GameplayManager::GameplayManager()
	: internal_clock(), frameLenght(sf::milliseconds(0)), t_events(0)
{
}

GameplayManager::~GameplayManager()
{
	clearTimedEvent();
}

void GameplayManager::forceClockReset()
{
	internal_clock.restart();
	frameLenght = sf::milliseconds(100);
}

sf::Time GameplayManager::deltaTime() const
{
	return frameLenght;
}

void GameplayManager::registerTimedEvent(TimedEvent* ev)
{
	t_events.push_back(ev);
}

void GameplayManager::clearTimedEvent()
{
	std::vector<TimedEvent*>::iterator it;

	for (it = t_events.begin(); it < t_events.end(); ++it)
	{
		if (*it != NULL) delete(*it);
		*it = NULL;
	}
}

void GameplayManager::preUpdate()
{
	frameLenght = internal_clock.restart();

	preUpdate_custom();
}

void GameplayManager::newEvent(const sf::Event& ev)
{
	newEvent_custom(ev);
}

void GameplayManager::gameplayUpdate()
{
	//Timed Events go first
	triggerTimedEvents();

	gameplayUpdate_custom();
}

void GameplayManager::postUpdate()
{
	postUpdate_custom();
}

void GameplayManager::triggerTimedEvents()
{
	std::vector<TimedEvent*>::iterator it;

	for (it = t_events.begin(); it < t_events.end(); ++it)
	{
		if (*it != NULL)
		{
			(*it)->check(deltaTime());
		}
	}
}

//Dummy customs so users don't have to reimplement everything if uneeded
void GameplayManager::preUpdate_custom() {}
void GameplayManager::newEvent_custom(const sf::Event& ev) {}
void GameplayManager::gameplayUpdate_custom() {}
void GameplayManager::postUpdate_custom() {}