#include "Door.h"

#include "Camera.h"
#include "Config.h"
#include "Game.h"
#include "SceneState.h"
#include "TextureID.h"
#include "TextureManager.h"

Door::Door(const LoaderParams& loader)
{
	setType(GameObjectType::DOOR);
	getRigidBody().setColliding(false);
	getTransform().getPosition() = glm::vec2(loader.m_x, loader.m_y);
	setRealCollisionRect(loader.m_realWidth, loader.m_realHeight);
	setWidth(loader.m_widthOfTexture);
	setHeight(loader.m_heightOfTexture);

	setAnimation(TextureManager::Instance().getAnimation(TextureID::DOOR));
}

Door::~Door()
{
}

void Door::draw()
{
	if (Config::SHOWING_DEBUG)
	{
		const SDL_Color redColor = { 255, 0, 0, 255 };
		const SDL_Rect collisionBox{ getTransform().getPosition().x - Camera::Instance().getPosition().x, getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight() };
		TextureManager::Instance().drawRect(collisionBox.x, collisionBox.y, collisionBox.w, collisionBox.h, redColor);
	}
	TextureManager::Instance().playAnimation(getAnimation(TextureID::DOOR), getTransform().getPosition().x - Camera::Instance().getPosition().x,
		getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.2f, 0.0f, 255);
}

void Door::update()
{
}

void Door::clean()
{
}

void Door::collision(DisplayObject* obj)
{
}
