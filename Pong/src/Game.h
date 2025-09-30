#pragma once

#include <SDL3/SDL.h>

struct Vector2
{
	float x;
	float y;
};


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

	SDL_Renderer* mRenderer;

	bool mIsRunning;

	Uint32 mTicksCount;

	Vector2 mPaddlePos;
	Vector2 mBallPos;

	int mPaddleDir;

	Vector2 mBallVel;
};