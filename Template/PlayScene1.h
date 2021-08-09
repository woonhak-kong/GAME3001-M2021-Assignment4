#pragma once
#ifndef __PLAY__SCENE1__
#define __PLAY__SCENE1__
#include "Level.h"
#include "Napkin.h"
#include "Node.h"
#include "Scene.h"
class Label;

class PlayScene1 : public Scene
{
public:
	PlayScene1();
	~PlayScene1();

	// Inherited via Scene
	void draw() override;
    void update() override;
    void clean() override;
	bool onExit() override;
	void handleEvents() override;
	bool onEnter() override;

	SceneState getState() override;


private:

	bool m_isHPushed;


	Label* m_score;

	SceneState m_state;
};

#endif // __PLAY__SCENE1__
