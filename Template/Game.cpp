#include "Game.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <SDL_ttf.h>

#include "ClearScene.h"
#include "EndScene.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "SceneState.h"
#include "FontManager.h"
#include "PlayScene1.h"
#include "SoundManager.h"
#include "StartScene.h"
#include "TextureManager.h"


//Game* Game::s_pInstance = nullptr;

// Game functions - DO NOT REMOVE ***********************************************

Game::Game() :
	m_bRunning(true),
	m_frames(0),
	m_deltaTime(0),
	m_mousePosition(glm::vec2()),
	m_pWindow(nullptr),
	m_sceneStateMachine(nullptr)
{
	srand(unsigned(time(nullptr)));  // random seed
}


void Game::init()
{
	m_bRunning = true;
}

bool Game::init(const char* title, const int x, const int y, const int width, const int height, const bool fullscreen)
{
	auto flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;

		// if succeeded create our window
		m_pWindow = (SDL_CreateWindow(title, x, y, width, height, flags));

		// if window creation successful create our renderer
		if (m_pWindow != nullptr)
		{
			std::cout << "window creation success" << std::endl;

			// create a new SDL Renderer and store it in the Singleton
			SDL_Renderer* renderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			TextureManager::Instance().setRenderer(renderer);
			//Renderer::Instance().setRenderer(renderer);

			if (renderer != nullptr) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}

			// IMGUI
			//ImGuiWindowFrame::Instance().Init();

			// Initialize Font Support
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				return false;
			}

			start();

		}
		else
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}

	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop

	return true;
}

void Game::start()
{
	m_sceneStateMachine = new GameSceneStateMachine();
	// in the first time, there is no scene. So, we need to push
	pushSceneState(SceneState::START_SCENE);
}

bool Game::isRunning() const
{
	return m_bRunning;
}


glm::vec2 Game::getMousePosition() const
{
	return m_mousePosition;
}

void Game::setFrames(const Uint32 frames)
{
	m_frames = frames;
}

Uint32 Game::getFrames() const
{
	return m_frames;
}

float Game::getDeltaTime() const
{
	return m_deltaTime;
}

void Game::setDeltaTime(const float time)
{
	m_deltaTime = time;
}

void Game::changeSceneState(const SceneState new_state)
{
		FontManager::Instance().clean();
		TextureManager::Instance().clean();
		EventManager::Instance().reset();
		switch (new_state)
		{
			case SceneState::START_SCENE:
				m_sceneStateMachine->changeState(new StartScene());
				std::cout << "start scene activated" << std::endl;
				break;
			case SceneState::TUTORIAL_SCENE:

				break;
			case SceneState::PLAY_SCENE1:
				m_sceneStateMachine->changeState(new PlayScene1());
				std::cout << "Play scene activated" << std::endl;
				break;
			case SceneState::END_SCENE:
				m_sceneStateMachine->changeState(new EndScene());
				std::cout << "End scene activated" << std::endl;
				break;
			case SceneState::CLEAR_SCENE:
				m_sceneStateMachine->changeState(new ClearScene());
				std::cout << "Clear scene activated" << std::endl;
				break;
			default:
				std::cout << "default case activated" << std::endl;
				break;
		}
}

void Game::pushSceneState(SceneState newState)
{
	switch (newState)
	{
		case SceneState::START_SCENE:
			m_sceneStateMachine->pushState(new StartScene());
			std::cout << "start scene activated" << std::endl;
			break;
		case SceneState::TUTORIAL_SCENE:

			break;
		case SceneState::PLAY_SCENE1:
			m_sceneStateMachine->pushState(new PlayScene1());
			std::cout << "Play scene activated" << std::endl;
			break;
		case SceneState::END_SCENE:
			m_sceneStateMachine->pushState(new EndScene());
			std::cout << "End scene activated" << std::endl;
			break;
		case SceneState::CLEAR_SCENE:
			m_sceneStateMachine->pushState(new ClearScene());
			std::cout << "Clear scene activated" << std::endl;
			break;
		default:
			std::cout << "default case activated" << std::endl;
			break;
	}

}

void Game::popSceneState()
{
	m_sceneStateMachine->popState();
}

void Game::quit()
{
	m_bRunning = false;
}

void Game::render() const
{
	SDL_SetRenderDrawColor(TextureManager::Instance().getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(TextureManager::Instance().getRenderer()); // clear the renderer to the draw colour

	m_sceneStateMachine->render();



	SDL_RenderPresent(TextureManager::Instance().getRenderer()); // draw to the screen

	//ImGuiWindowFrame::Instance().Render();
}

void Game::update() const
{
	m_sceneStateMachine->update();
}

void Game::clean() const
{
	std::cout << "cleaning game" << std::endl;

	// Clean Up for IMGUI
	//ImGui::DestroyContext();
	//ImGuiWindowFrame::Instance().Clean();
	delete m_sceneStateMachine;
	SoundManager::Instance().quit();
	//TextureManager::Instance().clean();
	// todo renderer delete
	//Game::Instance().clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(TextureManager::Instance().getRenderer());

	TTF_Quit();
	SDL_Quit();
}

void Game::handleEvents() const
{
	m_sceneStateMachine->handleEvents();
}
