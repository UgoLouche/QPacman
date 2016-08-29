#include "TimedEvent.h"

using namespace ProtoEng;

TimedEvent::TimedEvent(sf::Time time, bool recurrent) 
	: baseTime(time), remainingTime(time), isRecurrent(recurrent)
{
}

TimedEvent::~TimedEvent()
{
}

bool TimedEvent::check(sf::Time deltaTime)
{
	remainingTime -= deltaTime;

	if (remainingTime < sf::milliseconds(0))
	{
		trigger();
		return true;
	}
	else
		return false;
}

void TimedEvent::reArm()
{
	remainingTime = baseTime;
}

sf::Time TimedEvent::getRemainingTime() const
{
	return remainingTime;
}

 void TimedEvent::setBaseTime(sf::Time time)
{
	baseTime = time;
}

 sf::Time TimedEvent::getBaseTime() const
{
	return baseTime;
}

 bool TimedEvent::getIsRecurrent() const
{
	return isRecurrent;
}

 void TimedEvent::setReccurent(bool recurrent)
{
	isRecurrent = recurrent;
}

 void TimedEvent::trigger()
{
	trigger_custom();

	if (isRecurrent) reArm();
}

