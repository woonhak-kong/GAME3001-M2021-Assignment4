#pragma once
#ifndef __CLEAR_SCENE__
#define __CLEAR_SCENE__
#include "Button.h"
#include "Scene.h"
class ClearScene : public Scene
{
public:
	ClearScene();
	~ClearScene();

	void draw() override;
	void clean() override;
	void update() override;
	bool onExit() override;
	void handleEvents() override;
	bool onEnter() override;
	SceneState getState() override;

private:

	Button* m_pMenuButton;
	Button* m_pExitButton;
	SceneState m_state;
};

#endif // __CLEAR_SCENE__