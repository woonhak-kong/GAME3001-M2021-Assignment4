#include "PlayScene1.h"

#include "AttackBox.h"
#include "Background.h"
#include "CollisionManager.h"
#include "Config.h"
#include "EnemyKnight.h"
#include "LevelParser.h"
#include "EventManager.h"
#include "Game.h"
#include "Label.h"
#include "ScoreManager.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "StateParser.h"
#include "TextureManager.h"

PlayScene1::PlayScene1() :
	m_state(SceneState::PLAY_SCENE1),
	m_score(0),
	m_isHPushed(false)
{
}

PlayScene1::~PlayScene1()
{
}

void PlayScene1::draw()
{
	SDL_SetRenderDrawColor(TextureManager::Instance().getRenderer(), 0, 0, 255, 255);
	Scene::drawDisplayList();
	if (Config::SHOWING_DEBUG)
	{
		for (auto& nodeList : getNodeList())
		{
			for (auto& node : nodeList)
			{
				node.draw();
			}
		}
	}
	//m_testPlayer->draw();
}

void PlayScene1::update()
{
	Scene::updateDisplayList();
	//m_testPlayer->update();
	if (m_score != nullptr)
	{
		m_score->setText("Score : " + std::to_string(ScoreManager::getScore()));
	}
	// Checking all Collisions
	auto displayList = getDisplayList();
	//std::cout << displayList.size() << std::endl;
	for (auto iterA = displayList.begin(); iterA != displayList.end();)
	{
		DisplayObject* objA = *iterA;
		iterA++;
		for (auto iterB = iterA; iterB != displayList.end(); iterB++)
		{

			DisplayObject* objB = *iterB;
			if (objA->getType() != GameObjectType::NONE && objB->getType() != GameObjectType::NONE)
			{
				if (objA->getType() != objB->getType())
				{
					if (CollisionManager::AABBCheckByRealCollisionBox(objA, objB))
					{
						objA->collision(objB);
						objB->collision(objA);
					}
				}
			}
		}
	}


}

void PlayScene1::clean()
{
}

bool PlayScene1::onExit()
{
	Scene::removeAllChildren();
	SoundManager::Instance().clear();
	return true;
}

void PlayScene1::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_H))
	{
		if (!m_isHPushed)
		{
			if (Config::SHOWING_DEBUG)
			{
				Config::SHOWING_DEBUG = false;
			}
			else
			{
				Config::SHOWING_DEBUG = true;
			}
			m_isHPushed = true;
		}
	}
	else
	{
		m_isHPushed = false;
	}

}

bool PlayScene1::onEnter()
{
	SoundManager::Instance().load("assets/audio/rallyx_bgm.mp3", "bgm", SoundType::SOUND_MUSIC);
	SoundManager::Instance().load("assets/audio/sword1.wav", "attack", SoundType::SOUND_SFX);
	SoundManager::Instance().load("assets/audio/fire.wav", "fire", SoundType::SOUND_SFX);
	SoundManager::Instance().load("assets/audio/enemy_explosion1.wav", SoundID::ENEMY_EXPLOSION, SoundType::SOUND_SFX);
	SoundManager::Instance().setMusicVolume(1);
	SoundManager::Instance().setSoundVolume(1);
	// texture loading
	/*StateParser stateParser;
	stateParser.ParseState(Config::TEXTURE_LOCATION.c_str(), Config::PLAY_SCENE1);*/




	LevelParser levelParser;
	Level*  level = levelParser.ParseLevel(Config::SCENE1_LOCATION.c_str(), this);
	//addChild(level);

	m_score = new Label("Score : ", "Consolas", 30, { 0, 255, 0, 255 }, glm::vec2(1000, 50.0f));
	addChild(m_score,5);


	/*Napkin* player = new Napkin(LoaderParams(100, 400, 80, 70, 40, 70, 100, 20, "napkin"));
	addChild(player, 1);*/


	//EnemyKnight* enemy = new EnemyKnight(glm::vec2(300, 0), 200, 10, level->getCollisionLayers());
	//addChild(enemy);


	//addChild(new AttackBox(SDL_Rect{ 100,100,100,100 }, glm::vec2(10, 0), 100));

	//setPlayer(player);

	SoundManager::Instance().playMusic("bgm");
	return true;
}

SceneState PlayScene1::getState()
{
	return m_state;
}


