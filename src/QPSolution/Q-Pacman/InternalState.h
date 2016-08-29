#pragma once

#include "Directions.h"

#include "LoggedObject.h"

#include "SFML\Graphics.hpp"

#include <cstdint>
#include <list>

// Class representing internal State
// Based on an underlying 16 bit int
// X coord ->		bits 0-4 (up to 31)
// Y coord ->		bits 5-9 (up to 31, never more than 19 in practice)
// Direction ->		bits 10-11 (N, E, W, S)
// Super mode ->	bit 12 (yes/no)
// Unused bit ->	bits 13-15

//Everything gameplay element are based on this. Imovable objects only use
//first 10 bits, Ghosts use 2 more bits, Player use 13 bits.

//Since Player is quantum, it's in a superposition of all 2^16 states... 
//(see relevant code)

class InternalState : public ProtoEng::LoggedObject
{
public:
	//Statics
	//Masks
	static const uint16_t FULL = 0xFFFF;
	static const uint16_t COORD_X = 0x001F;
	static const uint16_t COORD_Y = 0x03E0;
	static const uint16_t DIRECTION = 0x0C00;
	static const uint16_t SUPER = 0x1000;
	static const uint16_t EXTRA = 0xE000;

	//Static Tool box for IS
	static InternalState int2is(uint16_t i);
	static uint16_t is2int(const InternalState& is);
	//Return all int that match the pattern on the specified bit from mask
	static std::list<uint16_t> patternMatch(uint16_t pattern, uint16_t mask);



	//Locals
	InternalState();
	InternalState(uint16_t state);
	InternalState(sf::Vector2i pos, Directions dir, bool super = false);
	~InternalState();

	//Getter
	sf::Vector2i getPosition() const;
	sf::Vector2i getDirectionOffset() const;
	sf::Vector2f getDrawPosition(float coeff) const;
	float getDirectionAngle() const; //Return the orientation corresponding t the current direction
	Directions getDirection() const;
	bool getSuper() const;
	uint16_t getIs() const;

	//Setter
	void setPosition(sf::Vector2i pos);
	void setDirection(Directions dir);
	void setSuper(bool isSuper);

private:
	//Static utility function
	static void construct_patternMatch(
		uint16_t pattern,
		uint16_t mask,
		std::list<uint16_t>& lst,
		size_t depth,
		uint16_t partial);



	//Internal Utility functions
	uint16_t applyMask(uint16_t mask) const;

	//Override
	virtual std::string custom_log_header() const override;


	//Attribute
	uint16_t state;
};