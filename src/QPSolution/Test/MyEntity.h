#pragma once

#include "SFML\Graphics.hpp"

class MyEntity : public sf::Drawable, public sf::Transformable
{
public:
	const static float speed;

	MyEntity();
	~MyEntity();

	void move(sf::Vector2f newPos);
	float getRadius();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::CircleShape shape;
};