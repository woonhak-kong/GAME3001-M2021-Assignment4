#pragma once
#ifndef __RIGID_BODY__
#define __RIGID_BODY__
#include <glm/vec2.hpp>

class RigidBody
{
public:
	RigidBody(float mass, const glm::vec2& velocity, const glm::vec2& acceleration, bool isColliding)
		: m_mass(mass),
		  m_velocity(velocity),
		  m_acceleration(acceleration),
		  m_isColliding(isColliding)
	{
	}


	float getMass() const
	{
		return m_mass;
	}

	void setMass(float mMass)
	{
		m_mass = mMass;
	}

	glm::vec2& getVelocity()
	{
		return m_velocity;
	}

	glm::vec2& getAcceleration()
	{
		return m_acceleration;
	}

	bool isColliding() const
	{
		return m_isColliding;
	}

	void setColliding(bool mIsColliding)
	{
		m_isColliding = mIsColliding;
	}

private:
	float m_mass;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	bool m_isColliding;
};

#endif //__RIGID_BODY__
