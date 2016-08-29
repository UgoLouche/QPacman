#include "Entity.h"

#include "QPacman.h"

#include "const.h"

Entity::Entity()
	: sprite(sf::Sprite()), animStep(0), parent(NULL), world(NULL)
{
}

Entity::Entity(QPacman * parent, QPWorld * world)
	: Entity()
{
	linkParent(parent);
	linkWorld(world);
}

Entity::~Entity()
{
}

void Entity::linkParent(QPacman * parent)
{
	this->parent = parent;
}

void Entity::linkWorld(QPWorld * world)
{
	this->world = world;
}

void Entity::changePlayerHealth(float delta)
{
	parent->changePlayerHealth(delta);
}

void Entity::changePlayerScore(float delta)
{
	parent->changePlayerScore(delta);
}

void Entity::playerGoSuper(sf::Vector2i pos)
{
	parent->playerGoSuper(pos);
}

const QPSpriteFactory& Entity::getFactory() const
{
	if (parent == NULL) errLog("Calling for Sprite Factory on a NULL parent");

	return parent->getSpriteFactory();
}

void Entity::setSprite(sf::Sprite sprite)
{
	this->sprite = sprite;
	this->sprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
	adjustOrigin();
}

void Entity::changeSpriteColor(sf::Color newCol)
{
	sprite.setColor(newCol);
}

void Entity::updateSprite(sf::Time deltaTime)
{
	animStep = (animStep + deltaTime.asMicroseconds()) % 1000000;

	this->sprite.setTextureRect(sf::IntRect( 
		(animStep / 100000) * CELL_SIZE, 
		0, 
		CELL_SIZE, 
		CELL_SIZE
	));
}

void Entity::setRandomBounds(int min, int max) const
{
	parent->setRandomBounds(min, max);
}

int Entity::nextRndInt() const
{
	return parent->nextRndInt();
}

const QPInput & Entity::getInputs() const
{
	return parent->getInput();
}

const QuantumEntity & Entity::getPlayer() const
{
	return parent->getPlayer();
}

void Entity::drawSprite(
	sf::RenderTarget& target, 
	sf::RenderStates states, 
	sf::Vector2f pos, 
	float angle,
	int alpha,
	bool superFilter) const
{
	sf::Sprite spr(sprite);

	if (superFilter) spr.setColor(sf::Color(100, 255, 100, alpha));
	else spr.setColor(spr.getColor() * sf::Color(255, 255, 255, alpha));

	target.draw(spr, states.transform.translate(pos).rotate(angle));
}

void Entity::adjustOrigin()
{
	sprite.setOrigin(CELL_SIZE / 2.0f, CELL_SIZE / 2.0f);
}
