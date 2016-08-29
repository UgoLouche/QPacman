#include "Directions.h"

Directions operator+(Directions d, int incr)
{
	if (incr == 0) return d;
	else if (incr > 0)
	{
		if (incr == 1)
		{
			switch (d)
			{
			default:
			case Directions::NORTH:
				return Directions::EAST;
			case Directions::EAST:
				return Directions::SOUTH;
			case Directions::SOUTH:
				return Directions::WEST;
			case Directions::WEST:
				return Directions::NORTH;
			}
		}
		else return ((d + 1) + (incr - 1));
	}
	else
	{
		if (incr == -1)
		{
			switch (d)
			{
			default:
			case Directions::NORTH:
				return Directions::WEST;
			case Directions::EAST:
				return Directions::NORTH;
			case Directions::SOUTH:
				return Directions::EAST;
			case Directions::WEST:
				return Directions::SOUTH;
			}
		}
		else return ( (d + -1) + (incr + 1) );
	}
}

Directions operator+(int incr, Directions d)
{
	return d + incr;
}
