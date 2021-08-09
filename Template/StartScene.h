#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Button.h"
#include "Scene.h"
#include "SDL.h"

#include "Level.h"
#include "Napkin.h"
#include "TestPlayer.h"


class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual bool onExit() override;
	virtual void handleEvents() override;
	virtual bool onEnter() override;

	virtual SceneState getState() override;

private:

	Button* m_pSartButton;
	Button* m_pExitButton;

	SceneState m_state;

};

#endif /* defined (__START_SCENE__) */