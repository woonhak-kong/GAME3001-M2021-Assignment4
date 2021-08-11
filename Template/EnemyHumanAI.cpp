#include "EnemyHumanAI.h"
#include <iostream>

#include "AttackAction.h"
#include "Character.h"
#include "CloseCombatCondition.h"
#include "CollisionManager.h"
#include "FleeAction.h"
#include "LOSCondition.h"
#include "LowHealthCondition.h"
#include "MoveToLOSAction.h"
#include "MoveToPlayerAction.h"
#include "PatrolAction.h"
#include "RadiusCondition.h"
#include "Scene.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "Util.h"

EnemyHumanAI::EnemyHumanAI(Character* character) :
	GameAI(character),
	m_previousPostion({ 0,0 })
{
	m_decisionTree = new DecisionTree();
	// Create and add root node.

	auto hpCondition = new LowHealthCondition(character);
	m_decisionTree->getTreeNodeList().push_back(hpCondition);

	TreeNode* fleeNode = m_decisionTree->AddNode(hpCondition, new FleeAction(character), TreeNodeType::RIGHT_TREE_NODE);
	m_decisionTree->getTreeNodeList().push_back(fleeNode);

	auto m_LOSNode = new LOSCondition(character);
	m_decisionTree->AddNode(hpCondition, m_LOSNode, TreeNodeType::LEFT_TREE_NODE);
	m_decisionTree->getTreeNodeList().push_back(m_LOSNode);

	auto m_RadiusNode = new RadiusCondition(character);
	m_decisionTree->AddNode(m_LOSNode, m_RadiusNode, TreeNodeType::LEFT_TREE_NODE);
	m_decisionTree->getTreeNodeList().push_back(m_RadiusNode);

	TreeNode* patrolNode = m_decisionTree->AddNode(m_RadiusNode, new PatrolAction(character), TreeNodeType::LEFT_TREE_NODE);
	m_decisionTree->getTreeNodeList().push_back(patrolNode);

	TreeNode* moveToLOS = m_decisionTree->AddNode(m_RadiusNode, new MoveToLOSAction(character), TreeNodeType::RIGHT_TREE_NODE);
	m_decisionTree->getTreeNodeList().push_back(moveToLOS);

	auto m_CloseCombatNode = new CloseCombatCondition(character);
	m_decisionTree->AddNode(m_LOSNode, m_CloseCombatNode, TreeNodeType::RIGHT_TREE_NODE);
	m_decisionTree->getTreeNodeList().push_back(m_CloseCombatNode);

	TreeNode* moveToPlayer = m_decisionTree->AddNode(m_CloseCombatNode, new MoveToPlayerAction(character), TreeNodeType::LEFT_TREE_NODE);
	m_decisionTree->getTreeNodeList().push_back(moveToPlayer);

	TreeNode* closeAttack = m_decisionTree->AddNode(m_CloseCombatNode, new AttackAction(character), TreeNodeType::RIGHT_TREE_NODE);
	m_decisionTree->getTreeNodeList().push_back(closeAttack);


	//auto aaa = m_decisionTree->getTreeNodeList()[0];

}

void EnemyHumanAI::update()
{
	m_decisionTree->MakeDecision();
	//auto player = m_self->getParent()->getPlayer();
	//glm::vec2 playerPosition = m_self->getParent()->getPlayer()->getCenterPosition();
	//glm::vec2 selfPosition = m_self->getCenterPosition();
	//glm::vec2 direction = playerPosition - selfPosition;

	//direction = Util::normalize(direction);
	//m_self->setCurrentDirection(direction);

	//bool losDistanceCheck = CollisionManager::lineRectCheck(selfPosition, selfPosition + m_self->getCurrentDirection() * m_self->getLOSDistance(),
	//	{ player->getRealCollisionRect().x, player->getRealCollisionRect().y }, player->getRealCollisionRect().w, player->getRealCollisionRect().h);

	//// if target is in range
	//if(losDistanceCheck)
	//{
	//	m_self->setDetectionRadius(true);
	//	// check if there is obstacle bewtween them.
	//	bool isObstacleThere = CollisionManager::LOSCheckWithNode(m_self, player);
	//	if (isObstacleThere)
	//	{
	//		//std::cout << "true "<< std::endl;
	//		m_self->setHasLOS(false);
	//	}
	//	else
	//	{
	//		m_self->setHasLOS(true);
	//	}

	//}
	//else
	//{
	//	m_self->setHasLOS(false);
	//	m_self->setDetectionRadius(false);
	//}

	////int distanceY = abs(playerPosition.y - selfPosition.y);
	////float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
	////int direction = 0;
	//////std::cout << "distance : " << distance << std::endl;

	////if (playerPosition.y > selfPosition.y - 100 && playerPosition.y < selfPosition.y + 100)
	////{

	//if (m_isGoingRight)
	//{
	//	m_self->moveToRight();
	//	if (selfPosition.x > 1000)
	//		m_isGoingRight = false;
	//}
	//else
	//{
	//	m_self->moveToLeft();
	//	if (selfPosition.x < 500)
	//		m_isGoingRight = true;
	//}

	//	if (distance > 500)
	//	{
	//		m_self->idle();
	//	}
	//	else
	//	{
	//		direction = playerPosition.x - selfPosition.x;
	//		if (distance > 50)
	//		{

	//			if (m_previousPostion.x == selfPosition.x && m_self->getCurrentState() == CharacterState::RUN)
	//			{
	//				m_self->jump();
	//			}
	//			if (direction < 0)
	//			{
	//				m_self->moveToLeft();
	//			}
	//			else if (direction > 0)
	//			{
	//				m_self->moveToRight();
	//			}
	//			m_previousPostion = selfPosition;
	//		}
	//		else
	//		{

	//			m_self->attack();

	//		}

	//	}
	//}
	//else
	//{
	//	m_self->idle();
	//}


}
