#include "InternalState.h"

#include "const.h"

#include <stdexcept>

InternalState InternalState::int2is(uint16_t i)
{
	return InternalState(i);
}

uint16_t InternalState::is2int(const InternalState& is)
{
	return is.getIs();
}

std::list<uint16_t> InternalState::patternMatch(uint16_t pattern, uint16_t mask)
{
	std::list<uint16_t> ret(0);
	construct_patternMatch(pattern, mask, ret, 0, 0x0000);

	return ret;
}

InternalState::InternalState()
	: state(0)
{
}

InternalState::InternalState(uint16_t state)
	: state(state)
{
}

InternalState::InternalState(sf::Vector2i pos, Directions dir, bool super)
	: InternalState()
{
	setPosition(pos);
	setDirection(dir);
	setSuper(super);
}

InternalState::~InternalState()
{
}

sf::Vector2i InternalState::getPosition() const
{
	return sf::Vector2i(applyMask(COORD_X), applyMask(COORD_Y) >> 5);
}

sf::Vector2i InternalState::getDirectionOffset() const
{
	sf::Vector2i ret;

	switch (getDirection())
	{
	case Directions::NORTH:
		ret = sf::Vector2i(0, -1);
		break;

	case Directions::EAST:
		ret = sf::Vector2i(1, 0);
		break;

	case Directions::SOUTH:
		ret = sf::Vector2i(0, 1);
		break;

	case Directions::WEST:
		ret = sf::Vector2i(-1, 0);
		break;

	default:
		ret = sf::Vector2i(0, 0);
		break;
	}

	return ret;
}

sf::Vector2f InternalState::getDrawPosition(float coeff) const
{
	sf::Vector2i curr_pos = getPosition();
	sf::Vector2i last_pos = curr_pos - getDirectionOffset();

	//1- Compute a weighted sum to locate drawing position between current and last board position
	//2- Multiply by Cell_SIZE to match pixel size of cells
	//3- Substract CELL_SIZE / 2 because sprites have their origin at their center
	return sf::Vector2f(
		CELL_SIZE * ((1 - coeff)*curr_pos.x + coeff * last_pos.x) + CELL_SIZE / 2.0f,
		CELL_SIZE * ((1 - coeff)*curr_pos.y + coeff * last_pos.y) + CELL_SIZE / 2.0f
	);
}

float InternalState::getDirectionAngle() const
{
	float ret;

	switch (getDirection())
	{
	case Directions::NORTH:
		ret = 0;
		break;

	case Directions::EAST:
		ret = 90;
		break;

	case Directions::SOUTH:
		ret = 180;
		break;

	case Directions::WEST:
		ret = -90;
		break;

	default:
		warnLog("Unknow direction in getDirectionAngle()");
		ret = 0;
		break;
	}

	return ret;
}

Directions InternalState::getDirection() const
{
	switch (applyMask(DIRECTION) >> 10)
	{
	case 0x0000:
		return Directions::NORTH;
		
	case 0x0001:
		return Directions::EAST;

	case 0x0002:
		return Directions::WEST;

	case 0x0003:
		return Directions::SOUTH;
		
	default:
		warnLog("Unknown direction in getDirection()");
		return Directions::NORTH;
	}
}

bool InternalState::getSuper() const
{
	if (applyMask(SUPER) >> 12) return true;
	else return false;
}

uint16_t InternalState::getIs() const
{
	return state;
}

void InternalState::setPosition(sf::Vector2i pos)
{
	uint16_t tmp = applyMask(~(COORD_X | COORD_Y));

	tmp |= (pos.y & 0x001F) << 5; //Take 5 first bit, and shift to the right place
	tmp |= pos.x & 0x001F; //Same

	state = tmp;
}

void InternalState::setDirection(Directions dir)
{
	uint16_t tmp = applyMask(~DIRECTION);

	switch (dir)
	{
	case Directions::NORTH:
		//Do nothing
		break;

	case Directions::EAST:
		tmp |= 0x0001 << 10;
		break;

	case Directions::WEST:
		tmp |= 0x0002 << 10;
		break;

	case Directions::SOUTH:
		tmp |= 0x0003 << 10;
		break;
	}

	state = tmp;
}

void InternalState::setSuper(bool isSuper)
{
	uint16_t tmp = applyMask(~SUPER);

	if (isSuper)
		tmp |= 0x0001 << 12; //Nothing to do otherwise

	state = tmp;
}

//This is basically a recursive binary search
void InternalState::construct_patternMatch(
	uint16_t pattern,                //The pattern to look for
	uint16_t mask,                   //The mask giving significative bit of the pattern
	std::list<uint16_t>& lst,        //Return container
	size_t depth,                    //the bit considered (left first so 0 is the 15th bit)
	uint16_t partial)                //Partial solution constructed through recursive call
{
	if (depth == INTERNAL_STATE_SIZE) //Nothing more to do
	{
		lst.push_back(partial);
		return;
	}

	//else
	uint16_t activeBit = 0x0001 << (INTERNAL_STATE_SIZE - 1 - depth);

	//Test mask value for the active bit
	if ( (activeBit & mask) == 0)
	{
		//ignore pattern and construct solutions with bot a 0 and a 1 for active bit
		construct_patternMatch(
			pattern,
			mask,
			lst,
			depth + 1,
			partial);

		construct_patternMatch(
			pattern,
			mask,
			lst,
			depth + 1,
			partial | activeBit);
	}
	else
	{
		//only construct solution with activeBit same as pattern
		construct_patternMatch(
			pattern,
			mask,
			lst,
			depth + 1,
			partial | (activeBit & pattern));
	}

	return;
}

uint16_t InternalState::applyMask(uint16_t mask) const
{
	return state & mask;
}

std::string InternalState::custom_log_header() const
{
	return "::InternalState::";
}
