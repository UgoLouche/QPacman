#include "GameView.h"

using namespace ProtoEng;

GameView::GameView() : linkedLayer(NULL)
{
}

GameView::GameView(Layer* layer) : GameView()
{
	linkedLayer = layer;
}

GameView::~GameView()
{
}

void GameView::assignLayer(Layer* layer)
{
	linkedLayer = layer;
}

Layer* GameView::getAssignedLayer() const
{
	return linkedLayer;
}

void GameView::setAnchor(sf::Vector2f pos)
{
	setCenter(sf::Vector2f( pos.x + (getSize().x / 2), pos.y + (getSize().y / 2) ));
}
