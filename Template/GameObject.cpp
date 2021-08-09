#include "GameObject.h"

#include <iostream>


GameObject::GameObject() :
	m_transform{glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0)},
	m_rigidBody{0, glm::vec2(0, 0), glm::vec2(0, 0), false},
	m_width(0),
	m_height(0),
	m_type(GameObjectType::NONE),
	m_enabled(true),
	m_visible(true)
{
}

Transform& GameObject::getTransform()
{
	return m_transform;
}

RigidBody& GameObject::getRigidBody()
{
	return m_rigidBody;
}

int GameObject::getWidth() const
{
	return m_width;
}

int GameObject::getHeight() const
{
	return m_height;
}

glm::vec2 GameObject::getCenterPosition()
{
	glm::vec2 position = getTransform().getPosition();
	position.x = position.x + getWidth() / 2;
	position.y = position.y + getHeight() / 2;
	return position;
}

SDL_Rect GameObject::getRealCollisionRect()
{
	if (m_collisionRect.w == 0 && m_collisionRect.h == 0)
	{
		std::cout << "ERROR - Set RealCollisionRect first!!!\n";
	}
	//std::cout << ((1 - ((float)m_collisionRect.w / getWidth())) / 2) * 100 << std::endl;
	m_collisionRect.x = (getTransform().getPosition().x + (m_width / 2.0f) - (m_collisionRect.w / 2.0f));
	m_collisionRect.y = getTransform().getPosition().y + (m_height / 2.0f) - (m_collisionRect.h / 2.0f);
	return m_collisionRect;
}

GameObjectType GameObject::getType() const
{
	return m_type;
}

void GameObject::setWidth(const int new_width)
{
	m_width = new_width;
}

void GameObject::setHeight(const int new_height)
{
	m_height = new_height;
}

void GameObject::setRealCollisionRect(int w, int h)
{
	m_collisionRect.w = w;
	m_collisionRect.h = h;
}

void GameObject::setType(const GameObjectType new_type)
{
	m_type = new_type;
}

void GameObject::setEnabled(const bool state)
{
	m_enabled = state;
}

bool GameObject::isEnabled() const
{
	return m_enabled;
}

void GameObject::setVisible(const bool state)
{
	m_visible = state;
}

bool GameObject::isVisible() const
{
	return m_visible;
}
