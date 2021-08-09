#include "AttackAction.h"

AttackAction::AttackAction(Character* character):
	ActionNode(character)
{
}

AttackAction::~AttackAction()
{
}

void AttackAction::Action()
{
	m_pCharacter->attack();
}
