#include "Game.h"

int main()
{
	Game game;

	bool success = game.Initilize();

	if (success)
	{
		game.RunLoop();
	}

	game.Shutdown();

	return 0;
}