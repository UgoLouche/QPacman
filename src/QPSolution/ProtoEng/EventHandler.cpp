#include "EventHandler.h"

using namespace ProtoEng;

EventHandler::~EventHandler()
{
}

void EventHandler::newEvent(const sf::Event& ev)
{
	handleEvent(ev);
}
