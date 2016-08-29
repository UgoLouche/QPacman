#include "QPacman.h"

#include "TestEntity.h"
#include "QuantumEntity.h"
#include "Entity.h"
#include "Gum.h"
#include "SuperGum.h"
#include "Ghost.h"

#include "boardMatrix.h"
#include "const.h"

#include "Box.h"
#include "GameView.h"
#include "LayerTypes.h"
#include "SimpleLogger.h"
#include "Container.h"
#include "Layer.h"

#include "SFML\Graphics.hpp"

#include <string>

QPacman::QPacman() :
	inputState(),
	isPaused(false),
	win(),
	world(),
	eventHandler(),
	spriteFactory(),
	logger("info.log", "warn.log", "error.log"),
	uiManager(),
	playerHealth(MAX_HEALTH),
	playerScore(0),
	rndManager()
{
}

QPacman::~QPacman()
{
}

void QPacman::launch()
{
	initialize();
	start();
}

void QPacman::quit()
{
	win.close();
}

const ProtoEng::GameWindow& QPacman::getWindow() const
{
	return win;
}

const QPLogger& QPacman::getLogger() const
{
	return logger;
}

const QPSpriteFactory& QPacman::getSpriteFactory() const
{
	return spriteFactory;
}

const QPInput & QPacman::getInput() const
{
	return inputState;
}

const QuantumEntity & QPacman::getPlayer() const
{
	return *(world.getPlayer());
}

void QPacman::inputEvent(uint16_t keyFlag)
{
	inputState.inputEvent(keyFlag);
	uiManager.inputNotify(keyFlag);
}

void QPacman::changePlayerHealth(float delta)
{
	playerHealth += delta;

	if (playerHealth <= 0)
	{
		playerHealth = 0;
		gameOver(true);
	}

	uiManager.healthUpdate(playerHealth);


}

void QPacman::changePlayerScore(float delta)
{
	playerScore += delta;
	uiManager.scoreUpdate(playerScore);
}

void QPacman::playerGoSuper(sf::Vector2i pos)
{
	world.getPlayer()->goSuper(pos);
}

void QPacman::setRandomBounds(int min, int max)
{
	//max - 1 in order to keep the [min, max) semantic I'm used too
	//Also because everything else is coded assuming that and I just realized my mistake now.
	rndManager.setIntBounds(min, max - 1);
}

int QPacman::nextRndInt() const
{
	return rndManager.nextInt();
}

void QPacman::pause()
{
	if (isPaused && isGameOver) return; //Do nothing

	isPaused = !isPaused;

	uiManager.pause(isPaused);
}

bool QPacman::pauseStatus() const
{
	return isPaused;
}

void QPacman::gameOver(bool isOver)
{
	isGameOver = isOver;
	isPaused = isOver;

	uiManager.gameOver(isGameOver);
}

void QPacman::restart()
{
	setBoard();
	gameOver(false);
}

void QPacman::setBoard()
{
	world.cleanEntities();

	playerHealth = MAX_HEALTH;
	playerScore = 0;

	//Test for view identification
	ProtoEng::Box* b1 = new ProtoEng::Box();
	b1->setPosition(sf::Vector2f(0, 0));
	b1->setDimensions(sf::Vector2f(WIN_WIDTH, WIN_HEIGHT - HUD_HEIGHT));
	b1->setBorderProperties(sf::Color::Cyan, 10);

	world.registerElement(LayerTypes::GameEntity, b1);

	//Grid Test
	ProtoEng::Box* b;
	for (int i = 0; i <= WIN_WIDTH - 25; i += 25)
	{
		for (int j = 0; j <= WIN_HEIGHT - HUD_HEIGHT - 25; j += 25)
		{
			b = new ProtoEng::Box();
			b->setPosition(sf::Vector2f((float)i, (float)j));
			b->setDimensions(sf::Vector2f(25, 25));
			b->setBorderProperties(sf::Color::Red, 2);
			world.registerElement(LayerTypes::GameEntity, b);
		}
	}

	//PLAYER SHOULD BE CREATED FIRST
	//Ghosts need a valid player to initialize
	//Otherwise you may delay initialization after creating everything ...
	//Test Player
	QuantumEntity* qe = new QuantumEntity(this, &world);
	qe->init();
	world.registerElement(LayerTypes::GameEntity, qe);
	world.newPlayer(qe);


	for (int i = 0; i < BOARDMATRIX.size(); ++i)
	{
		for (int j = 0; j < BOARDMATRIX[i].size(); ++j)
		{
			ClassicEntity* ent;

			switch (BOARDMATRIX[i][j])
			{
			default:
				warnLog("Unknown Value in BOARDMATRIX");
			case 0:
				continue; //do nothing on this iteration

			case 1:
				ent = new Gum(this, &world);
				ent->setPosition(sf::Vector2i(j, i));
				break;

			case 2:
				ent = new SuperGum(this, &world);
				ent->setPosition(sf::Vector2i(j, i));
				break;

			case 3:
				ent = new Ghost(this, &world);
				static_cast<Ghost*>(ent)->setPersonality(Personality::HUNTER);
				ent->setPosition(sf::Vector2i(j, i));
				static_cast<Ghost*>(ent)->resetAI();
				break;

			case 4:
				ent = new Ghost(this, &world);
				static_cast<Ghost*>(ent)->setPersonality(Personality::LAZY);
				ent->setPosition(sf::Vector2i(j, i));
				static_cast<Ghost*>(ent)->resetAI();
				break;

			case 5:
				ent = new Ghost(this, &world);
				static_cast<Ghost*>(ent)->setPersonality(Personality::RANDOM);
				ent->setPosition(sf::Vector2i(j, i));
				static_cast<Ghost*>(ent)->resetAI();
				break;

			case 6:
				ent = new Ghost(this, &world);
				static_cast<Ghost*>(ent)->setPersonality(Personality::MIMIC);
				ent->setPosition(sf::Vector2i(j, i));
				static_cast<Ghost*>(ent)->resetAI();
				break;
			}

			//Register ent
			world.registerElement(LayerTypes::GameEntity, ent);
			world.newEntity(ent);
		}
	}
}

void QPacman::initialize()
{
	//Logger
	logger.setMask(ProtoEng::SimpleLogger::ALL);
	logger.log(OPENING_STR, ProtoEng::SimpleLogger::ALL);
	linkLogger(&logger);

	//Create the window
	win.linkLogger(&logger);
	win.create(sf::VideoMode( (int)WIN_WIDTH, (int)WIN_HEIGHT), WIN_NAME);
	win.setActive();
	win.setGame(this);

	//World
	world.linkLogger(&logger);

	//Link eventHandler
	eventHandler.linkLogger(&logger);
	eventHandler.linkParent(this);

	//Link TurnHandler
	QPTurnHandler* turnHandler = new QPTurnHandler(sf::seconds(TURN_LENGHT), true);
	turnHandler->linkLogger(&logger);
	turnHandler->linkParent(this);
	turnHandler->linkWorld(&world);
	registerTimedEvent(turnHandler);


	//Setup views
	//NB: view ownership is taken by window

	//Game View
	ProtoEng::GameView* view1 = new ProtoEng::GameView();
	view1->setSize(WIN_WIDTH, WIN_HEIGHT - HUD_HEIGHT);
	view1->setViewport(sf::FloatRect(0, HUD_HEIGHT / WIN_HEIGHT, 1, 1 - HUD_HEIGHT / WIN_HEIGHT));
	view1->setAnchor(sf::Vector2f(0, 0));
	view1->assignLayer(world.getLayer(LayerTypes::GameEntity));

	//UI View
	ProtoEng::GameView* view2 = new ProtoEng::GameView();
	view2->setSize(WIN_WIDTH, HUD_HEIGHT);
	view2->setViewport(sf::FloatRect(0, 0, 1, HUD_HEIGHT / WIN_HEIGHT));
	view2->setAnchor(sf::Vector2f(0, 0));
	view2->assignLayer(world.getLayer(LayerTypes::GameUI));

	//Message View
	ProtoEng::GameView* view3 = new ProtoEng::GameView();
	view3->setSize(WIN_WIDTH, WIN_HEIGHT - HUD_HEIGHT);
	view3->setViewport(sf::FloatRect(0, HUD_HEIGHT / WIN_HEIGHT, 1, 1 - HUD_HEIGHT / WIN_HEIGHT));
	view3->setAnchor(sf::Vector2f(0, 0));
	view3->assignLayer(world.getLayer(LayerTypes::Message));
	
	win.registerView(view1);
	win.registerView(view2);
	win.registerView(view3);


	//UI
	uiManager.linkLogger(&logger);
	uiManager.init();

	//Main Container
	ProtoEng::Container* container_ui = new ProtoEng::Container();

	container_ui->setPosition(sf::Vector2f(0, 0));
	world.registerElement(LayerTypes::GameUI, container_ui);

	//Enclosing Box
	ProtoEng::Box* b2 = new ProtoEng::Box();
	b2->setPosition(sf::Vector2f(0, 0));
	b2->setDimensions(sf::Vector2f(WIN_WIDTH, HUD_HEIGHT));
	b2->setBorderProperties(sf::Color::Blue, 10);

	container_ui->registerItem(b2);

	//Fps Counter
	sf::Text* fps_counter = new sf::Text();
	fps_counter->setPosition(sf::Vector2f(700, 15));
	fps_counter->setCharacterSize(15);
	fps_counter->setString(FPS_TEXT);
	fps_counter->setFont(uiManager.getFont());

	container_ui->registerItem(fps_counter);
	uiManager.linkFps_counter(fps_counter);

	//Score
	sf::Text* score_counter = new sf::Text();
	score_counter->setPosition(sf::Vector2f(15, 15));
	score_counter->setCharacterSize(30);
	score_counter->setFont(uiManager.getFont());

	container_ui->registerItem(score_counter);
	uiManager.linkScore(score_counter);
	uiManager.scoreUpdate(0);


	//Health

	//Health decoration DO THIS FIRST OR IT WILL BE DRAW ON TOP OF THE REST
	ProtoEng::Box* health_box = new ProtoEng::Box();
	health_box->setPosition(sf::Vector2f(12, 52));
	health_box->setDimensions(sf::Vector2f(HEALTH_WIDTH + 6, HEALTH_HEIGHT + 6));
	health_box->setBorderProperties(sf::Color::Green, 3);

	container_ui->registerItem(health_box);

	//Dynamic UI element
	sf::RectangleShape* health_bar = new sf::RectangleShape();
	sf::Text* health_text = new sf::Text();

	health_bar->setPosition(sf::Vector2f(15, 55));
	health_bar->setFillColor(sf::Color::Red);

	health_text->setPosition(sf::Vector2f(20, 62.5));
	health_text->setCharacterSize(15);
	health_text->setFont(uiManager.getFont());

	container_ui->registerItem(health_bar);
	container_ui->registerItem(health_text);
	uiManager.linkHealthBar(health_bar);
	uiManager.linkHealth(health_text);
	uiManager.healthUpdate(MAX_HEALTH);

	//Key Buttons
	std::vector<sf::Sprite*> keyButtons(10, NULL);
	for (int i = 0; i < 10; ++i)
	{
		keyButtons[i] = new sf::Sprite();
		keyButtons[i]->setTexture(spriteFactory.getButtonTexture());
		keyButtons[i]->setTextureRect(sf::IntRect(0, i * UI_TEX_SIZE, UI_TEX_SIZE, UI_TEX_SIZE));
		keyButtons[i]->setPosition(sf::Vector2f(400.0f + (i * UI_TEX_SIZE), 15));
		
		container_ui->registerItem(keyButtons[i]);
	}
	
	uiManager.linkKeyButtons(keyButtons);

	//Game Message
	sf::Text* gameMessage = new sf::Text();
	sf::Text* subText = new sf::Text();

	gameMessage->setPosition(sf::Vector2f(WIN_WIDTH / 2, (WIN_HEIGHT - HUD_HEIGHT) / 2));
	gameMessage->setCharacterSize(30);
	gameMessage->setStyle(sf::Text::Bold);
	gameMessage->setFont(uiManager.getFont());

	subText->setPosition(gameMessage->getPosition() + sf::Vector2f(0, 30));
	subText->setCharacterSize(15);
	subText->setFont(uiManager.getFont());

	world.registerElement(LayerTypes::Message, gameMessage);
	world.registerElement(LayerTypes::Message, subText);
	uiManager.linkGameMessage(gameMessage, subText);

	//Create game object
	setBoard();
}

void QPacman::start()
{
	win.launch();
}

void QPacman::preUpdate_custom()
{
	if (!pauseStatus())
	{
		std::list<ClassicEntity*>::iterator it;
		std::list<ClassicEntity*> lst = world.getEntities();

		for (it = lst.begin(); it != lst.end(); ++it)
			(*it)->notifyGraphicUpdate(deltaTime());

		world.getPlayer()->notifyGraphicUpdate(deltaTime());
	}

	uiManager.notifyNewFrame(deltaTime());
}

void QPacman::newEvent_custom(const sf::Event& ev)
{
	eventHandler.newEvent(ev);
}

std::string QPacman::custom_log_header() const
{
	return "::QPacman::";
}
