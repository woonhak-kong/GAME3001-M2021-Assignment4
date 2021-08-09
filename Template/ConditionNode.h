#pragma once
#ifndef __CONDITION_NODE__
#define __CONDITION_NODE__
#include "Character.h"
#include "TreeNode.h"

// Interface
class ConditionNode : public TreeNode
{
public:
	ConditionNode(Character* character) : m_pCharacter(character)
	{
		isLeaf = false;
	}
	virtual ~ConditionNode() = default;

	virtual bool Condition() = 0;

	void setCharacter(Character* character) {
		m_pCharacter = character;
	}
protected:
	Character* m_pCharacter;
};

#endif /* defined (__CONDITION_NODE__) */
