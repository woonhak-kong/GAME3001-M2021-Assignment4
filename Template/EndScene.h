#pragma once
#ifndef __END_SCENE__
#define __END_SCENE__
#include "Button.h"
#include "Level.h"
#include "Napkin.h"
#include "Scene.h"
class EndScene : public Scene
{
public:
	EndScene();
	~EndScene();

	// Inherited via Scene
	void draw() override;
	void update() override;
	void clean() override;
	bool onExit() override;
	void handleEvents() override;
	bool onEnter() override;

	SceneState getState() override;

private:

	Button* m_pMenuButton;
	Button* m_pExitButton;
	SceneState m_state;
};

#endif // __END_SCENE__
