#include "ClockEvent.h"

ClockEvent::ClockEvent(int time, TimeUnit unit, MyClock* clock)
	: TimedEvent(), clock(clock), reArmCount(0), unit(unit)
{
	switch (unit)
	{
	case TimeUnit::milli:
		if (time < 100) time = 100; //Don't mess with sub_framerate refresh time
		setBaseTime(sf::milliseconds(time));
		break;

	case TimeUnit::sec:
		setBaseTime(sf::seconds(time));
		break;

	case TimeUnit::min:
		setBaseTime(sf::seconds(time * 60));
		break;

	case TimeUnit::hours:
		setBaseTime(sf::seconds(time * 60 * 60));
		break;

	default:
		break;
	}

	timeStep = time;

	setReccurent(true);
	reArm(); //just to be sure
}

void ClockEvent::trigger_custom()
{
	reArmCount++;

	switch (unit)
	{
	case TimeUnit::milli:
		clock->addTime(0, 0, 0, timeStep);
		break;

	case TimeUnit::sec:
		clock->addTime(0, 0, timeStep, 0);
		break;

	case TimeUnit::min:
		clock->addTime(0, timeStep, 0, 0);
		break;

	case TimeUnit::hours:
		clock->addTime(timeStep, 0, 0, 0);
		break;

	default:
		break;
	}
}
