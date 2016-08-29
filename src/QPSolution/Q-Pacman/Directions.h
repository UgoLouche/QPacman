#pragma once

enum class Directions
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 3,
	WEST = 2
};

Directions operator+(Directions d, int incr);
Directions operator+(int incr, Directions d);