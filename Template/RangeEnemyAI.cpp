#include "RangeEnemyAI.h"
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
#include "RangeCombatCondition.h"
#include "Scene.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "Util.h"


RangeEnemyAI::RangeEnemyAI(Character* character) :
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

	auto m_CloseCombatNode = new RangeCombatCondition(character);
	m_decisionTree->AddNode(m_LOSNode, m_CloseCombatNode, TreeNodeType::RIGHT_TREE_NODE);
	m_decisionTree->getTreeNodeList().push_back(m_CloseCombatNode);

	TreeNode* moveToPlayer = m_decisionTree->AddNode(m_CloseCombatNode, new MoveToPlayerAction(character), TreeNodeType::LEFT_TREE_NODE);
	m_decisionTree->getTreeNodeList().push_back(moveToPlayer);

	TreeNode* closeAttack = m_decisionTree->AddNode(m_CloseCombatNode, new AttackAction(character), TreeNodeType::RIGHT_TREE_NODE);
	m_decisionTree->getTreeNodeList().push_back(closeAttack);
}

void RangeEnemyAI::update()
{
	m_decisionTree->MakeDecision();
}
