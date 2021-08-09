#include "EnergyBar.h"

#include <iostream>

#include "TextureID.h"
#include "TextureManager.h"

EnergyBar::EnergyBar(int maxHp) :
	m_maxHp(maxHp),
	m_curHp(maxHp)
{
	getTransform().getPosition() = glm::vec2(20, 20);
	setWidth(350);
	setHeight(50);
}

void EnergyBar::draw()
{
	TextureManager::Instance().draw(TextureID::ENERGY_BACKGROUND, getTransform().getPosition().x, getTransform().getPosition().y, getWidth(), getHeight());
	TextureManager::Instance().drawFillRect(getTransform().getPosition().x + 25, getTransform().getPosition().y + 12, (getWidth() - 49) * ((float)m_curHp / m_maxHp), 26, { 200, 20, 0, 255 });
}

void EnergyBar::update()
{
}

void EnergyBar::clean()
{
}

void EnergyBar::setEnergy(float energy)
{
	if (energy > m_maxHp)
	{
		m_curHp = m_maxHp;
	}
	m_curHp = energy;
	std::cout << m_curHp << std::endl;
}
