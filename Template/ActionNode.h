#pragma once
#include "Character.h"
#include "TreeNode.h"

class ActionNode : public TreeNode
{
public:
	ActionNode() : m_pCharacter(nullptr) {
		isLeaf = true;
	}
	virtual ~ActionNode() = default;
	virtual void Action() = 0;

	void setCharacter(Character* character) {
		m_pCharacter = character;
	}

private:
	Character* m_pCharacter;

};
