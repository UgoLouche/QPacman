#include "QPacman.h"
#include "SimpleLogger.h"

#include "QuantumState.h"

#include "InternalState.h"
#include "Directions.h"
#include "SFML\Graphics.hpp"

int WinMain()
{
	QPacman game;

	//Test
	InternalState it;
	Directions dir;
	sf::Vector2i pos;
	bool super;

	for (int i = 0; i < 1000000; i++)
	{
		it.setPosition(sf::Vector2i(10, 25));
		it.setDirection(Directions::SOUTH);
		it.setSuper(true);
		it.setPosition(it.getPosition() + sf::Vector2i(4, -3));

		pos = it.getPosition();
		dir = it.getDirection();
		super = it.getSuper();
	}

	game.launch();

	return 0;
}