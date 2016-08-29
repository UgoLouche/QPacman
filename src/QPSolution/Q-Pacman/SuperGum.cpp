#include "SuperGum.h"

#include "QPSpriteFactory.h"
#include "QuantumEntity.h"

#include "const.h"

SuperGum::SuperGum()
{
	setRespawnCounter(GUM_RESPAWN);
}

SuperGum::SuperGum(QPacman * parent, QPWorld * wld)
	: ImmobileEntity(parent, wld)
{
	setRespawnCounter(GUM_RESPAWN);
	init();
}

SuperGum::~SuperGum()
{
}

void SuperGum::init()
{
	setSprite(getFactory().getSupGumSprite());
}

void SuperGum::act_custom()
{
	//Nothing to do
}

void SuperGum::collision_custom(float coeff, bool isSuper)
{
	//Remember this is called two times:  with non-super coeff THEN with super coeff
	//Do stuff when called with super as otherwise you risk to turn some state into super
	//and get their coeff again on the second call

	//If on non-super just do noithing and update integrity
	if (getIntegrity() < coeff) coeff = getIntegrity();

	if (isSuper) //Do stuff here
	{
		//This shouldn't happen except if first call coeff is magically exactly integrity ...
		if (getIntegrity() == 0) warnLog("Something Fishy...");

		playerGoSuper(getPosition());
	}

	setIntegrity(getIntegrity() - coeff);
}

std::string SuperGum::custom_log_header() const
{
	return "::SuperGum::";
}
