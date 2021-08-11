#pragma once
#ifndef __ENEMY_HUMAN2__
#define __ENEMY_HUMAN2__
#include "Character.h"
#include "Weapon.h"

class EnemyHuman2 : public Character
{
public:
	EnemyHuman2(const LoaderParams& loader);
	virtual ~EnemyHuman2();

	void draw() override;
	void update() override;
	void clean() override;

	void collision(DisplayObject* obj) override;

	void hit() override;
	void die() override;

	void attack() override;



private:
	Weapon* m_pWeapon;
	float m_attackDelay;

};

#endif // __ENEMY_HUMAN2__
