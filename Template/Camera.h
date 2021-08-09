#pragma once
#ifndef __CAMERA__
#define __CAMERA__
#include <glm/vec2.hpp>

#include "GameObject.h"

/**
 * if you wanna set camera, setTarget In target object,
 * and setting draw using getPosition()  EX) currentPosition - getPosition()
 *
 */
class Camera
{
public:

	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}

	void update(glm::vec2 velocity);
	void setTarget(glm::vec2* target);
	void setPosition(const glm::vec2& position);
	const glm::vec2 getPosition() const;

private:
	Camera();
	~Camera() = default;
	// the camera's target
	glm::vec2* m_pTarget;
	// the camera's position
	glm::vec2 m_position;
};

#endif // __CAMERA__
