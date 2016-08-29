#pragma once

#include "Entity.h"
#include "ActingObject.h"

#include "SFML\Graphics.hpp"

class ClassicEntity : public Entity, public ActingObject
{
public:
	ClassicEntity();
	ClassicEntity(QPacman* parent, QPWorld* world);
	virtual ~ClassicEntity();

	//Integrity Management
	void setIntegrity(float newIntegrity);
	float getIntegrity() const;
	void setRespawnCounter(int resp);

	//Compute If collision do happen, and proba of colisition
	void collision();

	//Position Setter
	void setPosition(sf::Vector2i pos);
	void setDirection(Directions dir);

	//Getter
	sf::Vector2i getPosition() const;
	Directions getDirection() const;
	sf::Vector2i getDirectionOffset() const;
	const InternalState& getIs() const;

protected:
	//Utility
	//Return the total probability of the player being at the current position (w/ or w/out super)
	float getPlayerProba(bool isSuper) const;
	float getPlayerProba(bool isSuper, InternalState is) const;

private:
	//Specific collision procedure. coeff is by how much the effect is applied
	//i.e. the probability of the player really being here.
	virtual void collision_custom(float coeff, bool isSuper) = 0;

	//Same Drawing procedure for all classic Entities
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void notifyGraphicUpdate_custom(sf::Time deltaTime);

	//Handle Board's edge transition
	//If an edge transition happenb, draw a partially "out of board" 'ghost' entity
	bool drawGhost;
	sf::Vector2i ghost_pos;

	InternalState iState;

	//Integrity (HP-like thing)
	float integrity;
	int respawnCounter;
	int respawnCounterBase;
};