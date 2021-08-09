#include "Node.h"

#include "TextureManager.h"

Node::Node() :
	m_nodeSize(0),
	m_x(0),
	m_y(0),
	m_row(0),
	m_col(0),
	m_isCollidable(false),
	m_isTransparent(false)
{
}

Node::Node(int x, int y, int row, int col, int size, bool collidable, bool isTransparent) :
	m_nodeSize(size),
	m_x(x),
	m_y(y),
	m_row(row),
	m_col(col),
	m_isCollidable(collidable),
	m_isTransparent(isTransparent)
{
}

Node::~Node()
{
}

void Node::draw()
{
	if (m_isTransparent)
	{
		TextureManager::Instance().drawRect(m_x, m_y, m_nodeSize, m_nodeSize, { 255,255,0,255 });
	}
	else if (m_isCollidable)
	{
		TextureManager::Instance().drawRect(m_x, m_y, m_nodeSize, m_nodeSize, { 255,0,0,255 });
	}
	SDL_RenderDrawPoint(TextureManager::Instance().getRenderer(), m_x, m_y);
}
