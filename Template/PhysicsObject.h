#pragma once
#include "Agent.h"
#include "Layer.h"
class PhysicsObject : public Agent
{
public:
	PhysicsObject();
	virtual ~PhysicsObject() = default;
	void draw() override;
	void update() override;
	void clean() override;

	void collision(DisplayObject* obj) override;

	bool isOnGround();
	float getFallingRate();

private:

	bool m_isCollision;
	bool m_isGroundCollision;
	SDL_Rect m_groundCollisionRect;
	const float m_fallingRate;
private:
	void m_setGravity();

};

