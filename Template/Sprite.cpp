#include "Sprite.h"

Sprite::Sprite() :
	m_pSpriteSheet(nullptr)
{
}


void Sprite::collision(DisplayObject* obj)
{
}

SpriteSheet* Sprite::getSpriteSheet()
{
	return m_pSpriteSheet;
}

Animation& Sprite::getAnimation(const std::string& state)
{
	return m_pAnimations[state];
}

void Sprite::setSpriteSheet(SpriteSheet* sprite_sheet)
{
	m_pSpriteSheet = sprite_sheet;
}

void Sprite::setAnimation(std::unordered_map<std::string, Animation> animation)
{
	m_pAnimations = animation;
}


//bool Sprite::m_animationExists(const std::string& id)
//{
//	return m_pAnimations.find(id) != m_pAnimations.end();
//}
