#include "Game.h"
#include "SDL3/SDL_video.h"

Game::Game() : mWindow(nullptr), mIsRunning(true)
{
}

bool Game::Initilize()
{

	bool sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (!sdlResult)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Pong", 1024, 768, 0);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput()
{
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
}
