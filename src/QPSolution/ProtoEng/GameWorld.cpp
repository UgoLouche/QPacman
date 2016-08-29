#include "GameWorld.h"

#include "Layer.h"

using namespace ProtoEng;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
	std::vector<Layer*>::iterator it;

	for (it = layers.begin(); it != layers.end(); ++it)
	{
		if (*it != NULL) delete(*it);
		*it = NULL;
	}
	layers.clear();
}

Layer * GameWorld::getLayer(int i)
{
	if (i >= layers.size())
	{
		layers.resize(i + 1, NULL);
	}

	if (layers[i] == NULL) layers[i] = new Layer();

	return layers[i];
}

Layer * GameWorld::getLayer(int i) const
{
	if (i >= layers.size())
		return NULL;
	else
		return layers[i];
}

void GameWorld::registerElement(int layerLevel, sf::Drawable * element)
{
	//Check for Layers' size
	if (layerLevel >= layers.size())
	{
		layers.resize(layerLevel + 1, NULL);
	}

	//Check that a layer do exists or create one
	if (layers[layerLevel] == NULL)
	{
		layers[layerLevel] = new Layer();
	}

	//add the element
	layers[layerLevel]->addElement(element);
}