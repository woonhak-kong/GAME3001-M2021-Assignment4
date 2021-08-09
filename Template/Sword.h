#pragma once
#ifndef __SWORD__
#define __SWORD__
#include "PhysicsObject.h"
#include "SwordType.h"

class Sword : public PhysicsObject
{
public:
	Sword(int x, int y, SwordType type);
	virtual ~Sword() = default;
	virtual void draw();
	void drawUi();
	virtual void update();
	virtual void clean();
	void collision(DisplayObject* obj) override;

	float getAttackSpeed() const;
	int getPower() const;
	int getReach() const;
	int getDurability() const;
	int getMaxDrability() const;
	SwordType getSwordType() const;

	void setDurability(int value);


private:

	float m_attackSpeed;
	int m_attackPower;
	int m_reach;
	int m_durability;
	int m_maxDurability;

	SwordType m_swordType;

};
#endif // __SWORD__