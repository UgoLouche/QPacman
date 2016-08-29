#pragma once

#include "Entity.h"
#include "ActingObject.h"
#include "QuantumState.h"

class QuantumEntity : public Entity, public ActingObject
{
public:
	QuantumEntity();
	QuantumEntity(QPacman* parent, QPWorld* wld);
	~QuantumEntity();

	void init();

	void goSuper(sf::Vector2i pos);

	//State Accessor
	//Flag is used to select the relevant arguments
	//If this is taking too much time in profiler
	//you can try catching full flags and act as a wrapper to operator[]
	//But I doubt it will ...
	float getProba(
		uint16_t flag, 
		sf::Vector2i pos = sf::Vector2i(0,0), 
		Directions dir = Directions::NORTH, 
		bool isSuper = false
	) const;
	float getProba(uint16_t flag, uint16_t base) const;

private:
	QuantumState state;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void notifyGraphicUpdate_custom(sf::Time deltaTime);
	virtual void act_custom() override;
};