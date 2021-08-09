#pragma once
#ifndef __ENERGY_BAR__
#define __ENERGY_BAR__
#include "Sprite.h"

class EnergyBar : Sprite
{
public:
	EnergyBar(int maxHp);
	~EnergyBar() = default;
	void draw() override;
	void update() override;
	void clean() override;

	void setEnergy(float energy);

private:

	SDL_Rect m_enegyRect;
	int m_maxHp;
	int m_curHp;

};

#endif // __ENERGY_BAR__