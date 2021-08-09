#pragma once
#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <SDL_rect.h>

#include "RigidBody.h"
#include "Transform.h"
#include "GameObjectType.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;

	// Draw the object
	virtual void draw() = 0;

	// Update the object
	virtual void update() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	Transform& getTransform();

	// getters and setters for physics properties
	RigidBody& getRigidBody();

	// getters and setters for game object properties
	int getWidth() const;
	int getHeight() const;
	glm::vec2 getCenterPosition();
	SDL_Rect getRealCollisionRect();
	void setWidth(int new_width);
	void setHeight(int new_height);
	void setRealCollisionRect(int w, int h);
	GameObjectType getType() const;
	void setType(GameObjectType new_type);

	void setEnabled(bool state);
	bool isEnabled() const;

	void setVisible(bool state);
	bool isVisible() const;

private:
	// transform component
	Transform m_transform;

	// rigid body component
	RigidBody m_rigidBody;

	// size variables
	int m_width;
	int m_height;

	SDL_Rect m_collisionRect;

	GameObjectType m_type;

	bool m_enabled;
	bool m_visible;
};
#endif // !__GAME_OBJECT__
