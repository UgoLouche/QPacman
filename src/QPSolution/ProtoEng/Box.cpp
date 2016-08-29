#include "Box.h"

using namespace ProtoEng;

Box::Box()
{
	border.setFillColor(sf::Color::Black);
	setBorderProperties(sf::Color::Green, 0.0f);
}

Box::Box(sf::Vector2f dimensions) 
	: Box()
{
	setDimensions(dimensions);
}

void Box::setBorderProperties(sf::Color color, float thickness)
{
	setBorderColor(color);
	setBorderThickness(thickness);
}

void Box::setBorderColor(sf::Color color)
{
	border.setOutlineColor(color);
}

void Box::setBorderThickness(float thickness)
{
	if (thickness > 0) thickness *= -1;

	border.setOutlineThickness(thickness);
}

void Box::setWidth(float width)
{
	sf::Vector2f size = border.getSize();

	size.x = width;
	border.setSize(size);
}

void Box::setHeight(float height)
{
	sf::Vector2f size = border.getSize();

	size.y = height;
	border.setSize(size);
}

void Box::setDimensions(sf::Vector2f dimensions)
{
	border.setSize(dimensions);
}

void Box::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(border, states.transform *  getTransform());
}
