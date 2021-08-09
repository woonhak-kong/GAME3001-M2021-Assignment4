#pragma once
#ifndef __GAME_SCENE_STATE_MACHINE__
#define __GAME_SCENE_STATE_MACHINE__

#include "Scene.h"
#include <vector>

class GameSceneStateMachine
{
public:
	GameSceneStateMachine();
	~GameSceneStateMachine();

	void pushState(Scene* pState);
	//void pushState(Scene* pState, bool stop);
	void changeState(Scene* pState);
	void popState();
	void update();
	void render();
	void handleEvents();
	void clearState();

private:
	void deleteState(); // this is queue for delete Scene

private:

	std::vector<Scene*> m_gameStates;
	std::vector<Scene*> m_deleteState;
	SceneState m_currentSceneState;


};
#endif // !__GAME_SCENE_STATE_MACHINE__