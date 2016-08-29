#include "Gum.h"

#include "QPSpriteFactory.h"

#include "const.h"

Gum::Gum()
{
	setRespawnCounter(GUM_RESPAWN);
}

Gum::Gum(QPacman * parent, QPWorld * wld)
	: ImmobileEntity(parent, wld)
{
	setRespawnCounter(GUM_RESPAWN);
	init();
}

Gum::~Gum()
{
}

void Gum::init()
{
	setSprite(getFactory().getGumSprite());
}

void Gum::act_custom()
{
	//Nothing to do
}

void Gum::collision_custom(float coeff, bool isSuper)
{
	if (getIntegrity() < coeff) coeff = getIntegrity();


	changePlayerScore(coeff * GUM_SCORE);

	setIntegrity(getIntegrity() - coeff);
}

std::string Gum::custom_log_header() const
{
	return "::Gum::";
}
