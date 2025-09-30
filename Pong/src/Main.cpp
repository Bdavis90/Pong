#include "Game.h"
#include <iostream>
int main()
{
	Game game;

	bool success = game.Initilize();

	if (success)
	{
		game.RunLoop();
	}

	game.Shutdown();

	std::cout << __cplusplus;
	return 0;
}