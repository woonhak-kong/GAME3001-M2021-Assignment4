#include "ClearScene.h"

#include "Config.h"
#include "EventManager.h"
#include "Game.h"
#include "Label.h"
#include "ScoreManager.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "StateParser.h"

ClearScene::ClearScene() :
	m_state(SceneState::CLEAR_SCENE)
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::draw()
{
	Scene::drawDisplayList();
}

void ClearScene::clean()
{
}

void ClearScene::update()
{
	Scene::updateDisplayList();
}

bool ClearScene::onExit()
{
	Scene::removeAllChildren();
	return true;
}

void ClearScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}
}

bool ClearScene::onEnter()
{
	StateParser stateParser;
	stateParser.ParseState(Config::TEXTURE_LOCATION.c_str(), Config::END_SCENE);

	Label* gameClear = new Label("Game Clear!!", "Consolas", 160, { 255,255,0,255 }, glm::vec2(Config::SCREEN_WIDTH / 2, 120.0f));
	addChild(gameClear);

	Label* gameScore = new Label("Score : " + std::to_string(ScoreManager::getScore()), "Consolas", 100, { 0,255,255,255 },
		glm::vec2(Config::SCREEN_WIDTH / 2, 250.0f));
	addChild(gameScore);

	m_pMenuButton = new Button("assets/UI/MenuButton.png", "menubutton", GameObjectType::MENU_BUTTON,
		glm::vec2(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2), true);
	m_pMenuButton->addEventListener(Event::CLICK, [&]() -> void
		{
			SoundManager::Instance().playSound(SoundID::BTN_CLICK);
			TheGame::Instance().changeSceneState(SceneState::START_SCENE);
		});
	m_pMenuButton->addEventListener(Event::MOUSE_OVER, [&]() -> void
		{
			m_pMenuButton->setAlpha(150);
			SoundManager::Instance().playSound(SoundID::BTN_HOVER);
		});

	m_pMenuButton->addEventListener(Event::MOUSE_OUT, [&]() -> void
		{
			m_pMenuButton->setAlpha(255);
		});

	addChild(m_pMenuButton);

	m_pExitButton = new Button("assets/UI/ExitButton.png", "exitbutton", GameObjectType::EXIT_BUTTON,
		glm::vec2(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2 + 120), true);
	m_pExitButton->addEventListener(Event::CLICK, [&]() -> void
		{
			SoundManager::Instance().playSound(SoundID::BTN_CLICK);
			TheGame::Instance().quit();
		});
	m_pExitButton->addEventListener(Event::MOUSE_OVER, [&]() -> void
		{
			m_pExitButton->setAlpha(150);
			SoundManager::Instance().playSound(SoundID::BTN_HOVER);
		});

	m_pExitButton->addEventListener(Event::MOUSE_OUT, [&]() -> void
		{
			m_pExitButton->setAlpha(255);
		});
	addChild(m_pExitButton);
	return true;
}

SceneState ClearScene::getState()
{
	return m_state;
}
