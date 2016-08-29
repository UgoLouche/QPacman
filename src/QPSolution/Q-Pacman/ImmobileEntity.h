#pragma once

#include "ClassicEntity.h"

//Inheritence is a bit ugly and could use differentiation between 
//Moving / Immobile Entities, but then TurnHandler and QPWorld should differentiate
//Moving entities (that are, entities who act AND collide) from 
//Immobile Entities (collide only)

class ImmobileEntity : public ClassicEntity
{
public:
	ImmobileEntity();
	ImmobileEntity(QPacman* parent, QPWorld* world);
	virtual ~ImmobileEntity();

private:
	//Override
	//Drawing is simpler since we don't move so we don't smooth movement
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};