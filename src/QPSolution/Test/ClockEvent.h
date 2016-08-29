#pragma once

#include "TimedEvent.h"
#include "MyClock.h"

enum TimeUnit
{
	milli = 1,
	sec = 2,
	min = 3,
	hours = 4,
};

class ClockEvent : public ProtoEng::TimedEvent
{
public:
	ClockEvent(int time, TimeUnit unit, MyClock* clock);
private:
	void trigger_custom();

	MyClock* clock;

	int reArmCount;
	TimeUnit unit;
	int timeStep;
};