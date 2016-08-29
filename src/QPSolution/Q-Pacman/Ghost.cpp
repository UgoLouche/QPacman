#include "Ghost.h"

#include "QuantumEntity.h"
#include "QPSpriteFactory.h"

#include "const.h"

Ghost::Ghost() : 
	perso(MIMIC),
	perso_cache(MIMIC),
	isChasing(false),
	scatterTimer(0),
	chaseTimer(0),
	internalTimer(0),
	targetTile(0xFFFF)
{
	setRespawnCounter(GHOSTS_RESPAWN);
}

Ghost::Ghost(QPacman * parent, QPWorld * wld, Personality perso) :
	ClassicEntity(parent, wld),
	perso(perso),
	perso_cache(perso),
	isChasing(false),
	scatterTimer(0),
	chaseTimer(0),
	internalTimer(0),
	targetTile(0xFFFF)
{
	setRespawnCounter(GHOSTS_RESPAWN);
	init();
}

Ghost::~Ghost()
{
}

void Ghost::init()
{
	setSprite(getFactory().getGhostSprite());
}

void Ghost::setPersonality(Personality perso)
{
	this->perso = perso;
	perso_cache = perso;

	switch (this->perso)
	{
	default:
		warnLog("set to unknown Personality");
	case MIMIC: //Not important, will be reset anyway (except for color)
	case HUNTER:
		changeSpriteColor(sf::Color(255, 255, 0));
		chaseTimer = HUNTER_CHASE_TIME;
		scatterTimer = HUNTER_SCATTER_TIME;
		break;

	case LAZY:
		changeSpriteColor(sf::Color(255, 0, 255));
		chaseTimer = LAZY_CHASE_TIME;
		scatterTimer = LAZY_SCATTER_TIME;
		break;

	case RANDOM:
		changeSpriteColor(sf::Color(0, 255, 255));
		chaseTimer = RANDOM_CHASE_TIME;
		scatterTimer = RANDOM_SCATTER_TIME;
	}
}

void Ghost::setPosition(sf::Vector2i pos)
{
	ClassicEntity::setPosition(pos);
}

void Ghost::resetAI()
{
	isChasing = !isChasing;
	switchMode();
}

Personality Ghost::getPersonality() const
{
	return perso_cache;
}

//1- Check everything's as expected
//2- Move to target
//3- Check if target is catched and/or timer is out and update
void Ghost::act_custom()
{
	//1- Check everything's as expected
	if (targetTile.getIs() == 0xFFFF || targetTile.getPosition() == getPosition())
	{
		warnLog("No Target Set / Target already on position");
		targetTile = getTarget();
	}

	if (internalTimer == 0)
	{
		warnLog("Inconsistent Timer Value");
		if (isChasing) internalTimer = chaseTimer;
		else internalTimer = scatterTimer;
	}


	//2- Move to target
	move();


	//3- Wrap up and check if target has been caught
	if (targetTile.getPosition() == getPosition())
	{
		if (isChasing) switchMode(); //Go back to scatter
		else //If scatter, pick a new target
		{
			do
			{
				targetTile = getTarget();
			} while (targetTile.getPosition() == getPosition());
		}
	}

	//Timer check
	if (--internalTimer == 0) switchMode();
}

void Ghost::collision_custom(float coeff, bool isSuper)
{
	for (int i = 0; i < 2; ++i) //Second time is to check crossOver
	{
		if (i == 1)
		{
			coeff = getPlayerProba(
				isSuper, 
				InternalState(getPosition() - getDirectionOffset(), getDirection() + 2)
			);
		}

		if (getIntegrity() < coeff) coeff = getIntegrity();

		if (isSuper)
		{
			if (coeff == 1)
			{
				printf("toto");
			}
			setIntegrity(getIntegrity() - coeff);
			changePlayerScore(coeff * GHOST_SCORE);
		}
		else changePlayerHealth(-1 * coeff * GHOSTS_DAMAGE);
	}
}

std::string Ghost::custom_log_header() const
{
	return "::Ghost::";
}

void Ghost::switchMode()
{
	//Mimic need to pick a new personality first
	if (perso == MIMIC)
	{
		setRandomBounds(0, 3); 
		switch (nextRndInt())
		{
		default:
			warnLog("Random out of bounds");
		case 0:
			changeSpriteColor(sf::Color(255, 255, 0));
			perso_cache = HUNTER;
			chaseTimer = HUNTER_CHASE_TIME;
			scatterTimer = HUNTER_SCATTER_TIME;
			break;
		case 1:
			changeSpriteColor(sf::Color(255, 0, 255));
			perso_cache = LAZY;
			chaseTimer = LAZY_CHASE_TIME;
			scatterTimer = LAZY_SCATTER_TIME;
			break;
		case 2:
			changeSpriteColor(sf::Color(0, 255, 255));
			perso_cache = RANDOM;
			chaseTimer = RANDOM_CHASE_TIME;
			scatterTimer = RANDOM_SCATTER_TIME;
			break;
		}
	}

	if (isChasing)
	{
		isChasing = false;
		internalTimer = scatterTimer;
		do
		{
			targetTile = getTarget();
		} while (targetTile.getPosition() == getPosition());
	}
	else
	{
		isChasing = true;
		internalTimer = chaseTimer;
		targetTile = getTarget();
		//If target is on ghost, go back for another round of scatter
		if (targetTile.getPosition() == getPosition()) switchMode(); 
	}
}

InternalState Ghost::getTarget() const
{
	if (isChasing) return chase_target();
	else return scatter_target();
}

InternalState Ghost::chase_target() const
{
	//Catch possible perso_cache inconsistencies
	if ( perso != MIMIC && perso != perso_cache )
	{
		warnLog("Inconsistent perso_cache");
		perso_cache = perso;
	}
	else if (perso_cache == MIMIC)
	{
		warnLog("Perso_cache set to MIMIC");
		perso_cache = HUNTER;
	}

	//Return the corresponding target
	switch (perso_cache)
	{
	default:
		warnLog("perso_cache unknown (despite previous check");
	case HUNTER:
		return hunterTarget();
		break;

	case LAZY:
		return lazyTarget();
		break;

	case RANDOM:
		return randomTarget();
		break;
	}
}

InternalState Ghost::scatter_target() const
{
	//Corner Bounds
	sf::Vector2i ret;
	int minX = 0;
	int maxX = 0;
	int minY = 0;
	int maxY = 0;

	switch (perso)
	{
	default:
		warnLog("Unknow personality for selecting scatter target");
	case HUNTER:
		minX = BOARD_WIDTH / 2;
		maxX = BOARD_WIDTH;
		minY = BOARD_HEIGHT / 2;
		maxY = BOARD_HEIGHT;
		break;

	case LAZY:
		minX = 0;
		maxX = BOARD_WIDTH / 2;
		minY = 0;
		maxY = BOARD_HEIGHT / 2;
		break;

	case RANDOM:
		minX = 0;
		maxX = BOARD_WIDTH / 2;
		minY = BOARD_HEIGHT / 2;
		maxY = BOARD_HEIGHT;
		break;

	case MIMIC:
		minX = BOARD_WIDTH / 2;
		maxX = BOARD_WIDTH;
		minY = 0;
		maxY = BOARD_HEIGHT / 2;
		break;
	}

	//Roll a target
	setRandomBounds(minX, maxX);
	ret.x = nextRndInt();
	setRandomBounds(minY, maxY);
	ret.y = nextRndInt();

	return InternalState(ret, Directions::NORTH); //Direction is arbitrary
}

InternalState Ghost::hunterTarget() const
{
	//Check for all possible pacman and keep the most probable one
	float maxProba = -1;
	float tmpProba;
	uint16_t index = 0;

	for (uint16_t i = 0x0000; i < (uint16_t)(~(InternalState::EXTRA)); ++i)
	{
		tmpProba = getPlayer().getProba(InternalState::FULL, i);

		if (tmpProba > maxProba)
		{
			maxProba = tmpProba;
			index = i;
		}
	}

	return InternalState(index);
}

InternalState Ghost::lazyTarget() const
{
	/* Look for all position on the board
	*  Start with the square of cell at a distance of 1 cell
	*  And increase the distance step by step
	*  At each step, you only need to check the boundaries of the square
	*  That is, when i is not at its maximal/minimal value, you can just check for
	*  Maximal / minimal value of j
	*
	*  Schematic representation wrt to the value of i
	*
	*             2 2 2 2 2
	*             2 1 1 1 2
	*             2 1 0 1 2
	*             2 1 1 1 2
	*             2 2 2 2 2
	*/
	int shiftVal = 0;

	while (1)
	{
		++shiftVal;

		for (int i = -shiftVal; i <= shiftVal; ++i)
		{
			for (int j = -shiftVal; j <= shiftVal; ++j)
			{
				sf::Vector2i pos(i, j);
				InternalState pattern = InternalState(pos, Directions::NORTH);
				uint16_t mask = InternalState::COORD_X | InternalState::COORD_Y | InternalState::EXTRA;
				std::list<uint16_t> matchingIstate = InternalState::patternMatch(pattern.getIs(), mask);

				//Take the first with non-null norm
				std::list<uint16_t>::iterator it;
				for (it = matchingIstate.begin(); it != matchingIstate.end(); ++it)
				{
					if (getPlayer().getProba(InternalState::FULL, *it) > 0)
					{
						return InternalState(*it);
					}
				}

				if (i == -shiftVal || i == shiftVal) j += 2 * shiftVal;
			}
			
		}
	}
}

InternalState Ghost::randomTarget() const
{
	//Roll a random position
	//Check if a Pacman exists in this position (for any direction and any super state)
	//Repeat until one is found
	while(1)
	{
		sf::Vector2i pos;
		setRandomBounds(0, BOARD_WIDTH);
		pos.x = nextRndInt();
		setRandomBounds(0, BOARD_HEIGHT);
		pos.y = nextRndInt();

		InternalState pattern = InternalState(pos, Directions::NORTH);
		uint16_t mask = InternalState::COORD_X | InternalState::COORD_Y | InternalState::EXTRA;
		std::list<uint16_t> matchingIstate = InternalState::patternMatch(pattern.getIs(), mask);

		//Take the first with non-null norm
		std::list<uint16_t>::iterator it;
		for (it = matchingIstate.begin(); it != matchingIstate.end(); ++it)
		{
			if (getPlayer().getProba(InternalState::FULL, *it) > 0)
			{
				return InternalState(*it);
			}
		}
	}
}

void Ghost::move()
{
	//Simulate target movement
	simulateInput();

	//Update direction wrt target
	setNewDirection();

	//Move
	setPosition(getPosition() + getDirectionOffset());
}

void Ghost::simulateInput()
{
	QPInput inputs = getInputs();

	if (isChasing) //Target is immobile in scatter mode
	{
		//Add an action for each input
		if (inputs.isKey1Pressed())
		{
			if (targetTile.getDirection() == Directions::EAST ||
				targetTile.getDirection() == Directions::WEST)
			{
				targetTile.setDirection(targetTile.getDirection() + 2);
			}
		}

		if (inputs.isKey2Pressed())
			targetTile.setDirection(targetTile.getDirection() + 2);

		if (inputs.isKey3Pressed()); //Not mapped yet

		if (inputs.isKey4Pressed())
			targetTile.setDirection(targetTile.getDirection() + -1);

		if (inputs.isKey5Pressed()) //Hadarm, get one at random
		{
			setRandomBounds(0, 4);
			targetTile.setDirection(targetTile.getDirection() + nextRndInt());
		}

		if (inputs.isKey6Pressed())
			targetTile.setDirection(targetTile.getDirection() + 1);

		if (inputs.isKey7Pressed()); //Not mapped yet

		if (inputs.isKey8Pressed()); //Not mapped yet

		if (inputs.isKey9Pressed()); //Not mapped yet

		//Move
		sf::Vector2i newPos = targetTile.getPosition() + targetTile.getDirectionOffset();

		if (newPos.x < 0)                             newPos.x += BOARD_WIDTH;
		else if (newPos.y < 0)                        newPos.y += BOARD_HEIGHT;
		else if (newPos.x > BOARD_WIDTH - 1)          newPos.x -= BOARD_WIDTH;
		else if (newPos.y > BOARD_HEIGHT - 1)         newPos.y -= BOARD_HEIGHT;

		targetTile.setPosition(newPos);
	}
}

void Ghost::setNewDirection()
{
	//This may return a "ghost" vector pointing toward an edge
	sf::Vector2i moveVector = getMoveVector(targetTile.getPosition());

	Directions moveDirection = getTargetDirection(moveVector);

	//Find a valid direction wrt moveDirection and update
	if (moveDirection == getReverseDirection())
	{
		//Pick a random Direction
		setRandomBounds(0, 2);
		if (nextRndInt() == 0) setDirection(moveDirection + 1);
		else setDirection(moveDirection + -1);
	}
	else setDirection(moveDirection);
}

//For each target position there exist 5 possible path
// 0- Direct path
// 1-4 Path through each edges of the board
//This function compute those 5 possible movevector and return the shortest
sf::Vector2i Ghost::getMoveVector(sf::Vector2i pos) const
{

	std::vector<sf::Vector2i> mvCandidates(5, sf::Vector2i(0, 0));

	mvCandidates[0] = pos - getPosition();
	mvCandidates[1] = sf::Vector2i(pos.x, pos.y - BOARD_HEIGHT) - getPosition();
	mvCandidates[2] = sf::Vector2i(pos.x, pos.y + BOARD_HEIGHT) - getPosition();
	mvCandidates[3] = sf::Vector2i(pos.x - BOARD_WIDTH, pos.y)  - getPosition();
	mvCandidates[4] = sf::Vector2i(pos.x + BOARD_WIDTH, pos.y)  - getPosition();

	//get the closest one. 
	float mindDist = getDistance( *(mvCandidates.begin()) );
	std::vector<sf::Vector2i>::iterator it_min = mvCandidates.begin();

	float minDist_tmp;
	std::vector<sf::Vector2i>::iterator it;
	for (it = mvCandidates.begin(); it != mvCandidates.end(); ++it)
	{
		minDist_tmp = getDistance( *it );

		if (minDist_tmp < mindDist)
		{
			mindDist = minDist_tmp;
			it_min = it;
		}
	}

	return *it_min;
}

float Ghost::getDistance(sf::Vector2i moveVector) const
{
	return (float)std::sqrt( std::pow(moveVector.x, 2) + std::pow(moveVector.y, 2) );
}

Directions Ghost::getTargetDirection(sf::Vector2i moveVector) const
{
	if (std::abs(moveVector.x) > std::abs(moveVector.y))
	{
		if (moveVector.x >= 0) return Directions::EAST;
		else return Directions::WEST;
	}
	else
	{
		if (moveVector.y >= 0) return Directions::SOUTH;
		else return Directions::NORTH;
	}
}

//Created before operator+ overload so it a bit dull now ...
Directions Ghost::getReverseDirection() const
{
	return getDirection() + 2;
}

