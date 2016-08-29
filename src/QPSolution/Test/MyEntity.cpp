#include "MyEntity.h"

const float MyEntity::speed = 100;

MyEntity::MyEntity()
{
	shape.setFillColor(sf::Color::Green);
	shape.setRadius(25);
}

MyEntity::~MyEntity()
{ }

void MyEntity::move(sf::Vector2f newPos)
{
	setPosition(newPos);
}

float MyEntity::getRadius()
{
	return shape.getRadius();
}

void MyEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states.transform * getTransform());
}