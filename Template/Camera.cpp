#include "Camera.h"

#include <iostream>

#include "Config.h"

void Camera::update(glm::vec2 velocity)
{
}

void Camera::setTarget(glm::vec2* target)
{
	m_pTarget = target;
}

void Camera::setPosition(const glm::vec2& position)
{
	m_position = position;
}

const glm::vec2 Camera::getPosition() const
{
	if (m_pTarget != nullptr)
	{
		glm::vec2 pos(m_pTarget->x - (Config::SCREEN_WIDTH / 2), m_pTarget->y - (Config::SCREEN_HEIGHT * 0.66));

		// todo if we want to set max size, modify here
		// we don't fix our max size of map yet.
		if (pos.x < 0)
		{
			pos.x = 0;
		}
		if (pos.x > Config::mapWidth - (Config::SCREEN_WIDTH))
		{
			pos.x = Config::mapWidth - (Config::SCREEN_WIDTH);
		}
		if (pos.y < 0)
		{
			pos.y = 0;
		}
		if (pos.y > Config::mapHeight - Config::SCREEN_HEIGHT)
		{
			pos.y = Config::mapHeight - Config::SCREEN_HEIGHT;
		}

		//std::cout << "x : " << pos.x << "    y : " << pos.y << std::endl;
		return pos;
	}

	return m_position;
}

Camera::Camera():
	m_pTarget(nullptr),
	m_position(glm::vec2(0.0f, 0.0f))
{
}
