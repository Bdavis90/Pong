#include "Game.h"
#include "SDL3/SDL_video.h"

const int thickness = 15;
const float paddleH = 100.f;

Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mPaddlePos()
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

	mRenderer = SDL_CreateRenderer(mWindow, NULL);
	if (!mRenderer)
	{
		SDL_Log("Failed to created renderer: %s", SDL_GetError());
		return false;
	}

	mPaddlePos.x = 10.f;
	mPaddlePos.y = 768.f / 2.f;
	mBallPos.x = 1024.f / 2.f;
	mBallPos.y = 768.f / 2.f;

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
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_QUIT:
				mIsRunning = false;
				break;
		}
	}

	const bool* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);

	// Draw walls
	// top wall

	SDL_FRect wall = { 0, 0, 1024, thickness };
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(mRenderer, &wall);

	// bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	// ball
	SDL_FRect ball = {
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	// paddle
	SDL_FRect paddle = {
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		paddleH
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	SDL_RenderPresent(mRenderer);
}
