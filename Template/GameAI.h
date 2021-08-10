#pragma once
#ifndef __GAME_AI__
#define __GAME_AI__
#include "DecisionTree.h"


class GameAI
{
public:
	friend class Character;
	GameAI(Character* character) : m_self(character), m_decisionTree(nullptr) {}
	virtual ~GameAI() = default;
	virtual void update() = 0;


protected:
	Character* m_self;
	DecisionTree* m_decisionTree;

};




#endif// __GAME_AI__
