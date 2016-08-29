#include "ClassicEntity.h"

#include "QuantumEntity.h"
#include "InternalState.h"

#include "const.h"

ClassicEntity::ClassicEntity() : 
	iState(0), 
	drawGhost(false), 
	ghost_pos(0, 0), 
	integrity(1), 
	respawnCounter(0), 
	respawnCounterBase(0)
{
}

ClassicEntity::ClassicEntity(QPacman * parent, QPWorld* world) : 
	Entity(parent, world), 
	iState(0), 
	drawGhost(false), 
	ghost_pos(0, 0), 
	integrity(1), 
	respawnCounter(0), 
	respawnCounterBase(0)
{
}

ClassicEntity::~ClassicEntity()
{
}

void ClassicEntity::setIntegrity(float newIntegrity)
{
	if (newIntegrity < 0) newIntegrity = 0;

	integrity = newIntegrity;
}

float ClassicEntity::getIntegrity() const
{
	return integrity;
}

void ClassicEntity::setRespawnCounter(int resp)
{
	respawnCounter = resp;
	respawnCounterBase = resp;
}

void ClassicEntity::collision()
{
	if (integrity > 0)
	{
		collision_custom(getPlayerProba(false), false);
		collision_custom(getPlayerProba(true), true);
	}
	else if (--respawnCounter == 0) //if Integrity depleted, count for respawn
	{
		respawnCounter = respawnCounterBase;
		integrity = 1;
	}
}

void ClassicEntity::setPosition(sf::Vector2i pos)
{
	//Cannot be out by more than 1 board (ie no while needed)
	//Cannot be out on both x and y (else if works fine)
	ghost_pos = pos;
	drawGhost = true;

	if (pos.x < 0)                     pos.x += BOARD_WIDTH;
	else if (pos.y < 0)                pos.y += BOARD_HEIGHT;
	else if (pos.x > BOARD_WIDTH - 1)  pos.x -= BOARD_WIDTH;
	else if (pos.y > BOARD_HEIGHT - 1) pos.y -= BOARD_HEIGHT;
	else drawGhost = false;

	iState.setPosition(pos);
}

void ClassicEntity::setDirection(Directions dir)
{
	iState.setDirection(dir);
}

sf::Vector2i ClassicEntity::getPosition() const
{
	return iState.getPosition();
}

Directions ClassicEntity::getDirection() const
{
	return iState.getDirection();
}

sf::Vector2i ClassicEntity::getDirectionOffset() const
{
	return iState.getDirectionOffset();
}

const InternalState& ClassicEntity::getIs() const
{
	return iState;
}

float ClassicEntity::getPlayerProba(bool isSuper) const
{

	return getPlayer().getProba(
		InternalState::COORD_X | InternalState::COORD_Y | InternalState::SUPER,
		getPosition(),
		getDirection(),
		isSuper
	);
}

float ClassicEntity::getPlayerProba(bool isSuper, InternalState is) const
{
	return getPlayer().getProba(
		InternalState::FULL,
		is.getPosition(),
		is.getDirection(),
		isSuper
	);
}

void ClassicEntity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//Get current and last positions
	sf::Vector2i curr_pos = iState.getPosition();
	sf::Vector2i last_pos = curr_pos - iState.getDirectionOffset();

	drawSprite(
		target, 
		states, 
		iState.getDrawPosition(getActionTimeRatio()), 
		iState.getDirectionAngle(),
		(int)(255 * integrity)
	);

	if (drawGhost) //Draw a second one
	{
		curr_pos = ghost_pos;
		last_pos = curr_pos - iState.getDirectionOffset();

		drawSprite(
			target,
			states,
			iState.getDrawPosition(getActionTimeRatio()),
			iState.getDirectionAngle(),
			(int)(255* integrity)
		);
	}
}

void ClassicEntity::notifyGraphicUpdate_custom(sf::Time deltaTime)
{
	updateSprite(deltaTime);
}
