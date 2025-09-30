#include "Game.h"
#include "SDL3/SDL_video.h"

const int thickness = 15;
const float paddleH = 100.f;

Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mTicksCount(0), mPaddleDir(0)
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

	mBallVel.x = -200.f;
	mBallVel.y = 235.f;

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

	mPaddleDir = 0;

	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}

	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

void Game::UpdateGame()
{
	// Frame Limiter 60fps
	const Uint32 timeout = mTicksCount + 16;
	Uint32 limiter = (timeout - SDL_GetTicks());

	while (limiter <= 0)
	{
		//currTime = SDL_GetTicks();
	}

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
	mTicksCount = SDL_GetTicks();

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.f * deltaTime;

		if (mPaddlePos.y < (paddleH / 2.f + thickness))
		{
			mPaddlePos.y = paddleH / 2.f + thickness;
		}
		else if (mPaddlePos.y > (768.f - paddleH / 2.f - thickness))
		{
			mPaddlePos.y = (768.f - paddleH / 2.f - thickness);
		}
	}

	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	float diff = mPaddlePos.y - mBallPos.y;
	diff = (diff > 0.f) ? diff : -diff;

	if (diff <= (paddleH / 2.f) && (mBallPos.x <= 25.f && mBallPos.x >= 20.f) && mBallVel.x < 0.f)
	{
		mBallVel.x *= -1.f;
	}

	// Top wall collision
	if (mBallPos.y <= thickness && mBallVel.y < 0.f)
	{
		mBallVel.y *= -1;
	}

	// Bottom wall collision
	else if (mBallPos.y >= (768 - thickness) && mBallVel.y > 0.f)
	{
		mBallVel.y *= -1;
	}
	else if (mBallPos.x >= (1024 - thickness) && mBallVel.x > 0.f)
	{
		mBallVel.x *= -1;
	}

	
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
		mBallPos.x - thickness / 2.f,
		mBallPos.y - thickness / 2.f,
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	// paddle
	SDL_FRect paddle = {
		mPaddlePos.x,
		mPaddlePos.y - paddleH / 2.f,
		thickness,
		paddleH
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	SDL_RenderPresent(mRenderer);
}
