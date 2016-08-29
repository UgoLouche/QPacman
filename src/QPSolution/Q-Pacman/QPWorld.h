#pragma once

#include "GameWorld.h"

#include <list>

class QuantumEntity;
class ClassicEntity;

class QPWorld : public ProtoEng::GameWorld
{
public:
	QPWorld();
	~QPWorld();


	//Entity Access
	std::list<ClassicEntity*>& getEntities();
	void newEntity(ClassicEntity* ent);
	void newPlayer(QuantumEntity* pl);
	QuantumEntity* getPlayer() const;

	void cleanEntities();


private:
	std::list<ClassicEntity*> entities;
	QuantumEntity* player;

};