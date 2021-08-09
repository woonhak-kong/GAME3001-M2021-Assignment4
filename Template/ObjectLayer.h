#pragma once
#include "Layer.h"
#include <vector>

#include "GameObject.h"

class ObjectLayer : public Layer
{
public:
	void draw() override;
	void update() override;
	void clean() override;

	std::vector<GameObject*>* getGameObjects();

private:
	std::vector<GameObject*> m_gameObjects;
};

