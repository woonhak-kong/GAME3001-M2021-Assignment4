#pragma once
#ifndef __DOOR__
#define __DOOR__
#include "LoaderParams.h"
#include "Sprite.h"
class Door : public Sprite
{
public:
	Door(const LoaderParams& loader);
	~Door();
	void draw() override;
	void update() override;
	void clean() override;

	void collision(DisplayObject* obj) override;
};

#endif // __DOOR__