#pragma once
#include "GameAI.h"
class Character;
class RangeEnemyAI : public GameAI
{
public:
	RangeEnemyAI(Character* character);
	~RangeEnemyAI() =default;
	void update() override;

private:
	glm::vec2 m_previousPostion;
};

