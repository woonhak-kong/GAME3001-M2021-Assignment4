#include "Weapon.h"

#include "TextureManager.h"

Weapon::Weapon(WeaponType type) :
	m_type(type)
{
	switch (m_type)
	{
		case WeaponType::WAND1:
			TextureManager::Instance().load("assets/objects/wand1.png", "wand1");
			break;
		case WeaponType::SWORD1:
			TextureManager::Instance().load("assets/objects/hammer1.png", "sword1");
			break;
	}
}

Weapon::~Weapon()
{
}

void Weapon::draw()
{
	switch (m_type)
	{
		case WeaponType::WAND1:
			TextureManager::Instance().draw("wand1", getTransform().getPosition().x, getTransform().getPosition().y, getCurrentHeading(), 255, true, SDL_FLIP_NONE);
			break;
		case WeaponType::SWORD1:
			TextureManager::Instance().draw("sword1", getTransform().getPosition().x, getTransform().getPosition().y, getCurrentHeading(), 255, true, SDL_FLIP_NONE);
			break;
	}

}

void Weapon::update()
{
}

void Weapon::clean()
{
}
