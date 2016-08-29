#pragma once

#include "ClassicEntity.h"

enum Personality
{
	HUNTER, //Chase most probable, scatter in bottom right
	LAZY,   //Chase closest, scatter in upper Left 
	RANDOM, //Random, probable pacman, scatter in bottom Left
	MIMIC,  //Pick a chase target according to a random strat (Hunter, Lazy, Random), scatter in upper Right
};

class Ghost : public ClassicEntity
{
public:
	Ghost();
	Ghost(QPacman* parent, QPWorld* wld, Personality perso = MIMIC);
	~Ghost();

	void init();
	void setPersonality(Personality perso);
	void setPosition(sf::Vector2i pos);

	void resetAI();

	Personality getPersonality() const; //Return mimiced personality in case of mimic

private:
	//Overrides
	virtual void act_custom() override;
	virtual void collision_custom(float coeff, bool isSuper) override;
	virtual std::string custom_log_header() const override;


	//AI Methods
	//Change mode
	void switchMode(); //Switch mode, reset timer, Handle MIMIC, also change target

	//Set Target
	InternalState getTarget() const; //Select a new Target
	InternalState chase_target() const;
	InternalState scatter_target() const;
	InternalState hunterTarget() const;
	InternalState lazyTarget() const;
	InternalState randomTarget() const;

	//Move
	void move();

	void simulateInput();

	void setNewDirection(); //Update direction and enforce rule (no U-turn and such ...)
	sf::Vector2i getMoveVector(sf::Vector2i pos) const;//Handle edge wrapping here
	float getDistance(sf::Vector2i moveVector) const; //Return the norm of the moveVector
	Directions getTargetDirection(sf::Vector2i moveVector) const; //Return the direction of the closest path to the target
	Directions getReverseDirection() const; //Get the inverse direction of the current one


	//Attribute
	Personality perso;
	mutable Personality perso_cache; //Currentpersonality (for mimic, and other)

	bool isChasing;

	size_t scatterTimer;
	size_t chaseTimer;
	size_t internalTimer;

	InternalState targetTile; //Use internal stat so you can simulate input
};
