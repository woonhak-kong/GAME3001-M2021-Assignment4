#include "TestPlayer.h"

#include "Camera.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Game.h"

TestPlayer::TestPlayer()
{

	m_rect = { 100, 100, 45, 60 };
	setWidth(45);
	setHeight(60);

	Camera::Instance().setTarget(&getTransform().getPosition());
}

void TestPlayer::draw()
{
	SDL_RenderDrawRect(TextureManager::Instance().getRenderer(), &m_rect);

		//TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX() - TheCamera::Instance()->getPosition().m_x, (Uint32)m_position.getY() - TheCamera::Instance()->getPosition().m_y,
		//	m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha, SDL_FLIP_HORIZONTAL);

}

void TestPlayer::update()
{
	handleEvent();

	glm::vec2 previousPosition = getTransform().getPosition();
	glm::vec2 newPosition = getTransform().getPosition() + (getRigidBody().getVelocity() * Game::Instance().getDeltaTime());
	getTransform().getPosition() = newPosition;
	if (CollisionManager::checkCollideTile(this, *m_pCollisionLayers))
	{
		std::cout << "cliide!!!!" << std::endl;
		getTransform().getPosition() = previousPosition;
	}
	m_rect.x = getTransform().getPosition().x - Camera::Instance().getPosition().x;
	m_rect.y = getTransform().getPosition().y - Camera::Instance().getPosition().y;
	//std::cout << " rect _ x : " << test.x << " y : " << getRigidBody().getVelocity().y << std::endl;
}

void TestPlayer::clean()
{
}

void TestPlayer::handleEvent()
{
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_RIGHT))
	{
		getRigidBody().getVelocity().x = 200;
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_LEFT))
	{
		getRigidBody().getVelocity().x = -200;
	}
	else
	{
		getRigidBody().getVelocity().x = 0;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_DOWN))
	{
		getRigidBody().getVelocity().y = 200;
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_UP))
	{
		getRigidBody().getVelocity().y = -200;
	}
	else
	{
		getRigidBody().getVelocity().y = 0;
	}
}

void TestPlayer::setCollisionLayers(std::vector<Layer*>* layers)
{
	m_pCollisionLayers = layers;
}
