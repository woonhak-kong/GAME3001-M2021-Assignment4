#pragma once
#ifndef __BOSS1__
#define __BOSS1__

#include "Character.h"
class Boss1 : public Character
{
public:
	Boss1(const LoaderParams& loader);
	~Boss1() = default;

	void draw() override;
	void update() override;
	void clean() override;
	void collision(DisplayObject* obj) override;
	void hit() override;
	void die() override;


};

#endif //__BOSS1__