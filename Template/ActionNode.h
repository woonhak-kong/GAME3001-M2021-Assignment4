#pragma once
#include "Character.h"
#include "TreeNode.h"

class ActionNode : public TreeNode
{
public:
	ActionNode(Character* character) : m_pCharacter(character), m_isActionDone(true) {
		isLeaf = true;
	}
	virtual ~ActionNode() = default;
	virtual void Action() = 0;

	void setCharacter(Character* character) {
		m_pCharacter = character;
	}
	void setActionDone(bool state)
	{
		std::cout << "actionDone" << std::endl;
		m_isActionDone = state;
	}

protected:
	Character* m_pCharacter;
	bool m_isActionDone;

};
