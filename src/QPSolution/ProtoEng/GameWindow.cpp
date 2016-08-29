#include "GameWindow.h"

#include "GameplayManager.h"
#include "GameView.h"
#include "Layer.h"


using namespace ProtoEng;

GameWindow::GameWindow()
{
	registeredView.clear(); //just to be sure
	setFramerateLimit(10);
}

GameWindow::GameWindow(sf::Vector2u size, std::string name) : GameWindow()
{
	setSize(size);
	setTitle(name);
}

GameWindow::~GameWindow()
{
	std::vector<GameView*>::iterator it;
	for (it = registeredView.begin(); it != registeredView.end(); ++it)
	{
		if (*it != NULL) delete(*it);
		*it = NULL;
	}

	registeredView.clear();
}

void GameWindow::registerView(GameView* view)
{
	registeredView.push_back(view);
}

 GameView * GameWindow::getView(int i) const
{
	return registeredView[i];
}

void GameWindow::setGame(GameplayManager* parent)
 {
	 this->parent = parent;
 }

 void GameWindow::launch()
 {
	 sf::Event ev;

	 parent->forceClockReset();
	 while (isOpen())
	 {
		 //Update Game World
		 parent->preUpdate();

		 while (pollEvent(ev)) parent->newEvent(ev);

		 parent->gameplayUpdate();

		 //Rendering
		 clear(sf::Color::Red);

		 std::vector<GameView*>::iterator itView;
		 for (itView = registeredView.begin(); itView != registeredView.end(); ++itView)
		 {
			 Layer* curr_layer = (*itView)->getAssignedLayer();
			 setView(**itView);

			 for (int i = 0; i < curr_layer->getSize(); i++)
			 {
				 draw(*(curr_layer->getElement(i)));
			 }
		 }

		 display();

		 //Post game update
		 parent->postUpdate();
	 }
 }
