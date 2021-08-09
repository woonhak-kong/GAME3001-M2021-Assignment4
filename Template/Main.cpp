
//#include <iostream>
//#include <Windows.h>

#include "Game.h"
#include "Config.h"
//#include "vld.h"
//#include <SDL.h>
//#define main main
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
	Uint32 frameStart, frameTime;
	Uint32 frames = 0;
	//AllocConsole();
	//freopen("CON", "w", stdout);

	TheGame::Instance().init("Napkin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, false);

	while (TheGame::Instance().isRunning())
	{
		frameStart = SDL_GetTicks();

		TheGame::Instance().handleEvents();
		TheGame::Instance().update();
		TheGame::Instance().render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(int(DELAY_TIME - frameTime));
		}

		// delta time
		float deltaTime = (SDL_GetTicks() - frameStart) / 1000.0f;
		TheGame::Instance().setDeltaTime(deltaTime);
		frames++;
		TheGame::Instance().setFrames(frames);

	}

	TheGame::Instance().clean();
	return 0;
}

