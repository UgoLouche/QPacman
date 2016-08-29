#include "QPWorld.h"

#include "LayerTypes.h"
#include "Layer.h"

QPWorld::QPWorld()
	: entities(0), player(NULL)
{
}

QPWorld::~QPWorld()
{
}

std::list<ClassicEntity*>& QPWorld::getEntities()
{
	return entities;
}

void QPWorld::newEntity(ClassicEntity * ent)
{
	entities.push_back(ent);
}

void QPWorld::newPlayer(QuantumEntity * pl)
{
	player = pl;
}

QuantumEntity * QPWorld::getPlayer() const
{
	return player;
}

void QPWorld::cleanEntities()
{
	getLayer(LayerTypes::GameEntity)->clearLayer();
	player = NULL;
	entities.clear();
}

