#include "Background.h"

#include "Config.h"
#include "TextureManager.h"

Background::Background(SceneState state):
	m_sceneState(state)
{
	switch (state)
	{
		case SceneState::TUTORIAL_SCENE:
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene0/plx-1.png", "background1");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene0/plx-2.png", "background2");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene0/plx-3.png", "background3");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene0/plx-4.png", "background4");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene0/plx-5.png", "background5");
			break;
		case SceneState::PLAY_SCENE1:
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background1.png", "background1");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background2.png", "background2");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background3.png", "background3");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background4.png", "background4");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background5.png", "background5");
			TextureManager::Instance().load("assets/maps/PixelPlatformerSet2v/Background/scene1/background6.png", "background6");
			break;
	}

	//setType(GameObjectType::NONE);
}

void Background::draw()
{
	switch (m_sceneState)
	{
		case SceneState::TUTORIAL_SCENE:
			TextureManager::Instance().draw("background1", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background2", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background3", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background4", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background5", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			break;
		case SceneState::PLAY_SCENE1:
			TextureManager::Instance().draw("background1", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background2", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background3", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background4", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background5", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			TextureManager::Instance().draw("background6", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
			break;
		default:
			break;
	}

}

void Background::update()
{
}

void Background::clean()
{
}
