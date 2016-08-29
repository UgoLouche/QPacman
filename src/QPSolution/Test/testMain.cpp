#include <SFML\Graphics.hpp>
#include "GameWindow.h"
#include "GameView.h"
#include "GameObject.h"

using namespace ProtoEng;

int WinMain()
{
	GameObject game;

	game.initialize();
	game.launch();

	return 0;
}