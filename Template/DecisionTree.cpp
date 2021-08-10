#include "DecisionTree.h"

#include "ActionNode.h"
#include "ConditionNode.h"

DecisionTree::DecisionTree()
{
}

DecisionTree::~DecisionTree()
{
}

std::map<std::string, DisplayObject*>& DecisionTree::getMap()
{
	std::map<std::string, DisplayObject*> aa;
	return aa;
}

TreeNode* DecisionTree::AddNode(TreeNode* parent, TreeNode* child_node, TreeNodeType type)
{
	switch (type)
	{
		case TreeNodeType::LEFT_TREE_NODE:
			parent->Left = child_node;
			break;
		case TreeNodeType::RIGHT_TREE_NODE:
			parent->Right = child_node;
			break;
	}
	child_node->Parent = parent;
	return child_node;
}

void DecisionTree::Display()
{
}

void DecisionTree::Update()
{
}

void DecisionTree::clean()
{
}

void DecisionTree::MakeDecision()
{
	//std::cout << "In MakeDecision..." << std::endl;
	TreeNode* currentNode = m_treeNodeList[0]; // Start at root node.

	while (!currentNode->isLeaf)
	{
		// currentNode = (currentNode->data) ? (currentNode->Right) : (currentNode->Left);
		currentNode = dynamic_cast<ConditionNode*>(currentNode)->Condition() ? (currentNode->Right) : (currentNode->Left);
	}
	// return currentNode->name; // Print out action's name.
	return static_cast<ActionNode*>(currentNode)->Action();
}

std::vector<TreeNode*>& DecisionTree::getTreeNodeList()
{
	return m_treeNodeList;
}
