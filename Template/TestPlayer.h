#pragma once
#ifndef __TESTPLAYER__
#define __TESTPLAYER__


#include "Sprite.h"
#include "TileLayer.h"

class TestPlayer : public Sprite
{
public:
	TestPlayer();
	~TestPlayer() = default;

	void draw() override;
	void update() override;
	void clean() override;
	void handleEvent();

	void setCollisionLayers(std::vector<Layer*>* layers);


private:

	SDL_Rect m_rect; // for test
	std::vector<Layer*>* m_pCollisionLayers;


};

#endif // __TESTPLAYER__