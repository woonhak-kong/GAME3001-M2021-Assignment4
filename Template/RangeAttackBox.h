#pragma once
#ifndef __RANGE_ATTACK_BOX__
#define __RANGE_ATTACK_BOX__
#include "Agent.h"
class RangeAttackBox : public Agent
{
public:
	RangeAttackBox(int x, int y, int w, int h, int power, GameObjectType attackType);
	~RangeAttackBox();
	void draw() override;
	void update() override;
	void clean() override;

	void collision(DisplayObject* obj) override;

	int getPower() const;


	int m_power;
};

#endif // __RANGE_ATTACK_BOX__