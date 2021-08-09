#pragma once
#ifndef __EXPLOSION__
#define __EXPLOSION__
#include "ExplosionType.h"
#include "Sprite.h"
class Explosion : public Sprite
{
public:
	Explosion(int x, int y, int width, int height, ExplosionType type);
	~Explosion() = default;
	void draw() override;
	void update() override;
	void clean() override;

private:
	ExplosionType m_type;
};

#endif// __EXPLOSION__