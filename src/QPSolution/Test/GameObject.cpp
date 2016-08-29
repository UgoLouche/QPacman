#include "GameObject.h"
#include "GameView.h"
#include "const.h"
#include "Box.h"
#include "MyEntity.h"
#include <iostream>
#include <string>
#include "ClockEvent.h"

GameObject::GameObject() : lenght(600), width(500)
{
	handler.linkParent(this); //In constructor because this is always the case
}

GameObject::~GameObject()
{
}

void GameObject::initialize()
{
	//Create the window
	win.create(sf::VideoMode((int)W_WIDTH, (int)W_HEIGHT), W_NAME);
	win.setActive();


	//Font Loading
	if (!font.loadFromFile("arial.ttf"))
	{
		exit(-1);
	}


	//Set Links
	win.setGame(this);


	//Setup Views - We use two non overlapping view, 
	//one for the Game and the other for the UI
	ProtoEng::GameView* view1 = new ProtoEng::GameView(); //Don't panic, view ownership is taken by window
	view1->setSize(VIEW1_WIDTH, W_HEIGHT);
	view1->setViewport(sf::FloatRect(0, 0, VIEW1_WIDTH / W_WIDTH, 1));
	view1->setAnchor(sf::Vector2f(0, 0)); //REMINDER: This is what the view SEE, not its position on the window
	view1->assignLayer(world.getLayer(LayerTypes::GameEntity));

	ProtoEng::GameView* view2 = new ProtoEng::GameView();
	view2->setSize(VIEW2_WIDTH, W_HEIGHT);
	view2->setViewport(sf::FloatRect(VIEW1_WIDTH / W_WIDTH, 0, VIEW2_WIDTH / W_WIDTH, 1));

	view2->setAnchor(sf::Vector2f(0, 0));
	view2->assignLayer(world.getLayer(LayerTypes::GameUI));

	win.registerView(view1);
	win.registerView(view2);


	//Populate game world

	//Create a bunch of boxes to show
	ProtoEng::Box* b1 = new ProtoEng::Box();
	b1->setPosition(sf::Vector2f(0, 0));
	b1->setDimensions(sf::Vector2f(VIEW1_WIDTH, W_HEIGHT));
	b1->setBorderProperties(sf::Color::Cyan, 10);

	ProtoEng::Box* b2 = new ProtoEng::Box();
	b2->setPosition(sf::Vector2f(0, 0));
	b2->setDimensions(sf::Vector2f(VIEW2_WIDTH, W_HEIGHT));
	b2->setBorderProperties(sf::Color::Blue, 10);

	world.registerElement(LayerTypes::GameEntity, b1);
	world.registerElement(LayerTypes::GameUI, b2);

	//MyEntity
	MyEntity* e1 = new MyEntity();
	e1->move(sf::Vector2f(50, 10));
	world.registerElement(LayerTypes::GameEntity, e1);
	setBall(e1);

	//Text
	text = new sf::Text();
	text->setFont(font);
	text->setString("FrameCount: " + std::to_string(frameCount));
	text->setCharacterSize(24);
	text->setColor(sf::Color::Red);
	text->setPosition(sf::Vector2f(10, 10));
	world.registerElement(LayerTypes::GameUI, text);

	//Timer
	clock = new MyClock();
	clock->reset();
	clock->setFont(font);
	clock->setPosition(sf::Vector2f(10, 40));
	world.registerElement(LayerTypes::GameUI, clock);

	//Timed Event
	ClockEvent* c1 = new ClockEvent(100, TimeUnit::milli, clock);
	//ClockEvent* c2 = new ClockEvent(1, TimeUnit::sec, clock);
	//ClockEvent* c3 = new ClockEvent(1, TimeUnit::min, clock);

	registerTimedEvent(c1);
	//registerTimedEvent(c2);
	//registerTimedEvent(c3);

}

void GameObject::launch()
{
	win.launch();
}

GameEventHandler GameObject::getHandler()
{
	return handler;
}

ProtoEng::GameWindow* GameObject::getWindow()
{
	return &win;
}

void GameObject::setBall(MyEntity* theBall)
{
	this->theBall = theBall;
}

void GameObject::newEvent_custom(const sf::Event& ev)
{
	handler.newEvent(ev);
}

void GameObject::gameplayUpdate_custom()
{
	sf::Vector2f pos = theBall->getPosition();


	if (handler.isKeyPressed(KeyValues::Z))
		pos.y -= deltaTime().asSeconds() * MyEntity::speed;

	if (handler.isKeyPressed(KeyValues::Q))
		pos.x -= deltaTime().asSeconds() * MyEntity::speed;

	if (handler.isKeyPressed(KeyValues::S))
		pos.y += deltaTime().asSeconds() * MyEntity::speed;

	if (handler.isKeyPressed(KeyValues::D))
		pos.x += deltaTime().asSeconds() * MyEntity::speed;

	//Bound checking
	if (pos.x < 0)
		pos.x = 0;

	if (pos.x > width - 2 * (theBall->getRadius()))
		pos.x = width - 2 * (theBall->getRadius());

	if (pos.y < 0)
		pos.y = 0;

	if (pos.y > lenght - 2 * (theBall->getRadius()))
		pos.y = lenght - 2 * (theBall->getRadius());

	theBall->setPosition(pos);

	frameCount++;
	text->setString("FrameCount: " + std::to_string(frameCount));

}