#pragma once
#ifndef __ENEMY_HUMAN1__
#define __ENEMY_HUMAN1__
#include "Character.h"
#include "Weapon.h"

class EnemyHuman1 : public Character
{
public:
	EnemyHuman1(const LoaderParams& loader);
	virtual ~EnemyHuman1();

	void draw() override;
	void update() override;
	void clean() override;

	void collision(DisplayObject* obj) override;

	void hit() override;
	void die() override;




private:
	Weapon* m_pWeapon;

};

#endif // __ENEMY_HUMAN1__
