#include "TestEntity.h"

#include "QPSpriteFactory.h"

TestEntity::TestEntity()
	: stepCount(0)
{
}

TestEntity::TestEntity(QPacman * parent, QPWorld * wld)
	: ClassicEntity(parent, wld), stepCount(0)
{
	init();
}

TestEntity::~TestEntity()
{
}

void TestEntity::init()
{
	setSprite(getFactory().getTestSprite());
}

void TestEntity::act_custom()
{
	stepCount++;
	stepCount %= 35;

	if (stepCount == 5)
	{
		switch (getDirection())
		{
		case Directions::NORTH:
			setDirection(Directions::EAST);
			break;

		case Directions::EAST:
			setDirection(Directions::SOUTH);
			break;

		case Directions::SOUTH:
			setDirection(Directions::WEST);
			break;

		case Directions::WEST:
			setDirection(Directions::NORTH);
			break;
		}
	}

	setPosition(getPosition() + getDirectionOffset());
}

void TestEntity::collision_custom(float coeff, bool isSuper)
{
}

std::string TestEntity::custom_log_header() const
{
	return "::TestEntity::";
}
