#include "EndScene.h"

#include "Button.h"
#include "EventManager.h"
#include "Game.h"
#include "Label.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "StateParser.h"

EndScene::EndScene() :
	m_state(SceneState::END_SCENE)
{
}

EndScene::~EndScene()
{
}

void EndScene::draw()
{
	Scene::drawDisplayList();
}

void EndScene::update()
{
	Scene::updateDisplayList();
}

void EndScene::clean()
{
}

bool EndScene::onExit()
{
	Scene::removeAllChildren();
	return true;
}

void EndScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}
}

bool EndScene::onEnter()
{

	StateParser stateParser;
	stateParser.ParseState(Config::TEXTURE_LOCATION.c_str(), Config::END_SCENE);

	Label* gameOver = new Label("Game Over", "lazy", 200, { 255,0,0,255 }, glm::vec2(Config::SCREEN_WIDTH / 2, 120.0f));
	addChild(gameOver);

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

SceneState EndScene::getState()
{
	return m_state;
}

