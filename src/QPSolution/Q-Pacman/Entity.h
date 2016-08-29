#pragma once

#include "InternalState.h"
#include "Directions.h"
#include "QPLogger.h"
#include "QPInput.h"

#include "LoggedObject.h"

#include "SFML\Graphics.hpp"

class QPacman;
class QPWorld;
class QPSpriteFactory;
class QuantumEntity;

class Entity : public sf::Drawable, public virtual ProtoEng::LoggedObject
{
public:
	Entity();
	Entity(QPacman* parent, QPWorld* world);
	virtual ~Entity();

	void linkParent(QPacman* parent);
	void linkWorld(QPWorld* world);

	//Player effect
	void changePlayerHealth(float delta);
	void changePlayerScore(float delta);
	void playerGoSuper(sf::Vector2i pos);

protected:
	//Internal Getter
	const QPSpriteFactory& getFactory() const;
	const QPInput& getInputs() const;
	const QuantumEntity& getPlayer() const;

	void setSprite(sf::Sprite sprite);
	void changeSpriteColor(sf::Color newCol);
	void updateSprite(sf::Time deltaTime);

	//Randum Number
	void setRandomBounds(int min, int max) const;
	int nextRndInt() const;


	//Drawing primitive
	//Draw the sprite at the specified location with specified rotation
	void drawSprite(
		sf::RenderTarget& target,
		sf::RenderStates states,
		sf::Vector2f pos,
		float angle, 
		int alpha = 255,
		bool superFilter = false) const;


private:
	//Ad-hoc utility
	void adjustOrigin();

	sf::Sprite sprite;
	int animStep;

	QPacman* parent;
	QPWorld* world;


};