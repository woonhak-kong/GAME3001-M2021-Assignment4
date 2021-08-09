#include "KnightAI.h"

#include <iostream>

#include "Character.h"
#include "Scene.h"

KnightAI::KnightAI(Character* character) :
	GameAI(character)
{
}

void KnightAI::update()
{
	glm::vec2 playerPosition = m_self->getParent()->getPlayer()->getTransform().getPosition();
	glm::vec2 selfPosition = m_self->getTransform().getPosition();
	int distance = abs(playerPosition.x - selfPosition.x);
	//std::cout << "distance : " << distance << std::endl;
	if (distance > 100)
	{
		m_self->idle();
	}
	else
	{
		m_self->moveToRight();
	}




}
