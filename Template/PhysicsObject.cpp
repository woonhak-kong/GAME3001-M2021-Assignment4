#include "PhysicsObject.h"

#include <algorithm>

#include "Camera.h"
#include "CollisionManager.h"
#include "Config.h"
#include "Game.h"
#include "TextureManager.h"

PhysicsObject::PhysicsObject() :
	m_isCollision(false),
	m_isGroundCollision(false),
	m_fallingRate(100.0f)
{
}

void PhysicsObject::draw()
{
	const SDL_Color greenColor = { 0, 255, 0, 255 };
	const SDL_Color redColor = { 255, 0, 0, 255 };

	if (Config::SHOWING_DEBUG)
	{
		const SDL_Rect collisionBox{ getRealCollisionRect().x, getRealCollisionRect().y, getRealCollisionRect().w, getRealCollisionRect().h };
		if (m_isCollision)
		{
			TextureManager::Instance().drawRect(collisionBox.x, collisionBox.y, collisionBox.w, collisionBox.h, redColor);
		}
		else
		{
			TextureManager::Instance().drawRect(collisionBox.x, collisionBox.y, collisionBox.w, collisionBox.h, greenColor);
		}
		if (m_isGroundCollision)
		{
			TextureManager::Instance().drawRect(m_groundCollisionRect.x, m_groundCollisionRect.y, m_groundCollisionRect.w, m_groundCollisionRect.h, redColor);
		}
		else
		{
			TextureManager::Instance().drawRect(m_groundCollisionRect.x, m_groundCollisionRect.y, m_groundCollisionRect.w, m_groundCollisionRect.h, greenColor);
		}
	}
}

void PhysicsObject::update()
{
	SDL_Rect newCollidePosition;
	newCollidePosition.x = m_groundCollisionRect.x;
	newCollidePosition.y = m_groundCollisionRect.y;
	newCollidePosition.w = m_groundCollisionRect.w;
	newCollidePosition.h = m_groundCollisionRect.h;




	newCollidePosition.x = floor(m_groundCollisionRect.x + getRigidBody().getVelocity().x * Game::Instance().getDeltaTime());
	if (!CollisionManager::checkCollideTile(newCollidePosition, getParent()->getNodeList()))
	{
		getTransform().getPosition().x = floor(getTransform().getPosition().x + getRigidBody().getVelocity().x * Game::Instance().getDeltaTime());
	}
	else
	{
		newCollidePosition.x = m_groundCollisionRect.x;
	}


	newCollidePosition.y = floor(m_groundCollisionRect.y + getRigidBody().getVelocity().y * Game::Instance().getDeltaTime());
	if (!CollisionManager::checkCollideTile(newCollidePosition, getParent()->getNodeList()))
	{
		getTransform().getPosition().y = floor(getTransform().getPosition().y + getRigidBody().getVelocity().y * Game::Instance().getDeltaTime());
	}
	else
	{
		newCollidePosition.y = m_groundCollisionRect.y;
	}


	m_groundCollisionRect.x = getRealCollisionRect().x;
	m_groundCollisionRect.y = getRealCollisionRect().y + getRealCollisionRect().h;
	m_groundCollisionRect.w = getRealCollisionRect().w;
	m_groundCollisionRect.h = 5;
}

void PhysicsObject::clean()
{
}

void PhysicsObject::collision(DisplayObject* obj)
{
}

bool PhysicsObject::isOnGround()
{
	return m_isGroundCollision;
}

float PhysicsObject::getFallingRate()
{
	return m_fallingRate;
}

SDL_Rect PhysicsObject::getGroundCollision() const
{
	return m_groundCollisionRect;
}

void PhysicsObject::m_setGravity()
{
	getRigidBody().getVelocity().y += Config::GRAVITY * getRigidBody().getMass();
	getRigidBody().getVelocity().y = std::clamp(getRigidBody().getVelocity().y, -(getRigidBody().getMass() * m_fallingRate), (getRigidBody().getMass() * m_fallingRate));
}
