#pragma once
#ifndef __WEAPON__
#define __WEAPON__
#include "Agent.h"
#include "WeaponType.h"

class Weapon : public Agent
{
public:
	Weapon(WeaponType type);
	virtual ~Weapon();

	void draw() override;
	void update() override;
	void clean() override;


private:

	WeaponType m_type;

};

#endif // __WEAPON__