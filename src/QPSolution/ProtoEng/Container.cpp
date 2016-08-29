#include "Container.h"

using namespace ProtoEng;

Container::Container()
	: items(0)
{
}

Container::~Container()
{
	std::list<sf::Drawable*>::iterator it;

	for (it = items.begin(); it != items.end(); ++it)
	{
		if (*it != NULL) delete(*it);
		*it = NULL;
	}
}

void Container::registerItem(sf::Drawable * item)
{
	items.push_back(item);
}

void Container::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	std::list<sf::Drawable*>::const_iterator it;
	
	states.transform *= getTransform();

	draw_custom(target, states);

	for (it = items.begin(); it != items.end(); ++it)
		target.draw(**it, states);
}

void Container::draw_custom(sf::RenderTarget & target, sf::RenderStates combinedState) const
{
}
