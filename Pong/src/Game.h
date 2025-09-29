#pragma once

#include <SDL3/SDL.h>

class Game {
public:

	Game();

	bool Initilize();
	void RunLoop();
	void Shutdown();

private:

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;

	bool mIsRunning;
};