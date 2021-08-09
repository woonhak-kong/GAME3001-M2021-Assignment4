#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "DisplayObject.h"
#include "SceneState.h"

class Background : public DisplayObject
{
public:
	Background(SceneState state);
	~Background() = default;
	void draw() override;
	void update() override;
	void clean() override;

private:

	SceneState m_sceneState;
	// temporary

};

#endif // __BACKGROUND__