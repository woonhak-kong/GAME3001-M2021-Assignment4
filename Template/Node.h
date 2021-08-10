#pragma once
#ifndef __NODE__
#define __NODE__
#include <map>
#include <glm/vec2.hpp>

#include "Label.h"
#include "NodeStatus.h"

enum class NeighbourDirection
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NUM_OF_DIRECTION
};

class Node
{
public:
	Node();
	Node(int x, int y, int row, int col, int size, bool collidable, bool isTransparent);
	virtual ~Node();
	void draw();
	void setParrentTile(Node* parrent);
	void setStatus(NodeStatus status);

	std::map<NeighbourDirection, Node*>& getNeighbourMap();
	Node* getParrentTile();
	NodeStatus getStatus() const;

	int m_nodeSize;
	glm::vec2 m_position;
	int m_x;
	int m_y;
	int m_row;
	int m_col;
	bool m_isCollidable;
	bool m_isTransparent;
	int m_f;
	int m_g;
	int m_h;

	Label m_label;
	NodeStatus m_status;
	Node* m_parrentTile;
	std::map<NeighbourDirection, Node*> m_neighbourMap;
};


#endif // __NODE__
