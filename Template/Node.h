#pragma once
#ifndef __NODE__
#define __NODE__
#include <glm/vec2.hpp>

class Node
{
public:
	Node();
	Node(int x, int y, int row, int col, int size, bool collidable, bool isTransparent);
	virtual ~Node();
	void draw();



	int m_nodeSize;
	glm::vec2 m_position;
	int m_x;
	int m_y;
	int m_row;
	int m_col;
	bool m_isCollidable;
	bool m_isTransparent;


};


#endif // __NODE__
