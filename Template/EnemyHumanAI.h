#pragma once
#ifndef __ENEMY_HUMAN_AI__
#define __ENEMY_HUMAN_AI__
#include <glm/vec2.hpp>

#include "GameAI.h"

class Character;
class EnemyHumanAI : public GameAI
{
public:
	EnemyHumanAI(Character* character);
	~EnemyHumanAI() = default;
	void update() override;

private:

	glm::vec2 m_previousPostion;
	bool m_isGoingRight;
};

#endif // __ENEMY_HUMAN_AI__