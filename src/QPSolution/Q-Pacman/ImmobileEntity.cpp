#include "ImmobileEntity.h"

ImmobileEntity::ImmobileEntity()
{
}

ImmobileEntity::ImmobileEntity(QPacman * parent, QPWorld * world)
	: ClassicEntity(parent, world)
{
}

ImmobileEntity::~ImmobileEntity()
{
}

void ImmobileEntity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	drawSprite(
		target, 
		states, 
		getIs().getDrawPosition(0), 
		getIs().getDirectionAngle(), 
		(int)(255 * getIntegrity())
	);
}
