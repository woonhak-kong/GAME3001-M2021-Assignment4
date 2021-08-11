#pragma once
#ifndef __DECISION_TREE__
#define __DECISION_TREE__
#include <map>
#include <vector>


#include "DisplayObject.h"
#include "TreeNode.h"
#include "TreeNodeType.h"

class DecisionTree
{
public:
	DecisionTree();
	~DecisionTree();

	// getters and setters
	//
	//Agent* getAgent() const;
	/*LOSCondition* getLOSNode() const;
	RadiusCondition* getRadiusNode() const;
	CloseCombatCondition* getCloseCombatNode() const;*/
	//void setAgent(Agent* agent);
	std::map<std::string, DisplayObject*>& getMap();

	// convenience functions
	TreeNode* AddNode(TreeNode* parent, TreeNode* child_node, TreeNodeType type);
	void Display();
	void Update();
	void clean();

	void MakeDecision(); // in order traversal

	std::vector<TreeNode*>& getTreeNodeList();

private:
	//Agent* m_agent;

	/*LOSCondition* m_LOSNode;
	RadiusCondition* m_RadiusNode;
	CloseCombatCondition* m_CloseCombatNode;*/

	//void m_buildTree();

	std::vector<TreeNode*> m_treeNodeList;
	std::map<std::string, DisplayObject*> m_targets;
	TreeNode* m_pPrevNode;

};
#endif // __DECISION_TREE__
