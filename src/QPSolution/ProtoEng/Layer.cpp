#include "Layer.h"

using namespace ProtoEng;

Layer::~Layer()
{
	clearLayer();
}

void Layer::addElement(sf::Drawable * element)
{
	elements.push_back(element);
}

sf::Drawable * Layer::getElement(int i) const
{
	return elements[i];
}

size_t Layer::getSize() const
{
	return elements.size();
}

void Layer::clearLayer()
{
	std::vector<sf::Drawable*>::iterator it;

	for (it = elements.begin(); it != elements.end(); ++it)
	{
		if (*it != NULL) delete(*it);
		*it = NULL;
	}
	elements.clear();
}
