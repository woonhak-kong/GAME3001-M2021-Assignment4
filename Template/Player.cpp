#include "Player.h"

#include <iostream>

#include "AttackBox.h"
#include "Camera.h"
#include "Config.h"
#include "EventManager.h"
#include "MouseButtons.h"
#include "RangeAttackBox.h"
#include "Scene.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Util.h"

Player::Player(const LoaderParams& loader) :
	Character(loader),
	m_pWeapon(nullptr),
	m_isLeftClick(false),
	m_isRightClick(false),
	m_gameOver(false)
{

	Animation animation = Animation();
	Frame frame;
	glm::vec2 size;
	std::string animationName = "player";

	TextureManager::Instance().load("assets/characters/player/idle.png", "idle");
	TextureManager::Instance().load("assets/characters/player/run.png", "run");
	size = glm::vec2(16, 16);

	animation.name = "idle";
	for (int i = 0; i < 4; ++i)
	{
		frame.name = "idle";
		frame.x = size.x * i;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	animation.name = "run";
	for (int i = 0; i < 4; ++i)
	{
		frame.name = "run";
		frame.x = size.x * i;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	setAnimation(TextureManager::Instance().getAnimation("player"));

	m_pWeapon = new Weapon(WeaponType::WAND1);

	setLOSDistance(300.f);
	setHasLOS(false);
	setType(GameObjectType::PLAYER);
}

Player::~Player()
{

}

void Player::draw()
{
	Character::draw();
	/*TextureManager::Instance().draw("napkin", getTransform().getPosition().x - Camera::Instance().getPosition().x,
		getTransform().getPosition().y - Camera::Instance().getPosition().y , getWidth(), getHeight(),  0, 255);*/
	int alpha = 255;
	/*if (m_hitMotionNum > 0)
	{
		if (m_hitMotionNum % 2 == 0)
		{
			alpha = 20;
		}
		else
		{
			alpha = 255;
		}
		m_hitMotionNum--;
	}
	else
	{
		alpha = 255;
	}*/
	SDL_RendererFlip flip;
	//flip = isFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	if (getCurrentDirection().x < 0)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		flip = SDL_FLIP_NONE;
	}

	switch (getCurrentState())
	{
		case CharacterState::IDLE:
			TextureManager::Instance().playAnimation(getAnimation("idle"), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, getAlpha(), flip);

			break;
		case CharacterState::RUN:
			TextureManager::Instance().playAnimation(getAnimation("run"), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, getAlpha(), flip);

			break;
		case CharacterState::ATTACK:
			TextureManager::Instance().playAnimation(getAnimation("attack2"), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getHeight(), getAttackSpeed(), 0.0f, getAlpha(), flip, true, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ATTACK_BOX:

							break;
						case CallbackType::ANIMATION_END:

							break;
						default:
							break;
					}
				}, 3);
			break;
		case CharacterState::DEAD:
			TextureManager::Instance().playAnimation(getAnimation("idle"), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, getAlpha(), flip, false, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ANIMATION_END:
							m_gameOver = true;
							break;
						default:
							break;
					}
				});
			break;
	}

	m_pWeapon->draw();
	m_pWeapon->setCurrentHeading(90.f);
	//this->setCurrentHeading(90.0f);
	//this->setLOSDistance(300.f);

	if (Config::SHOWING_DEBUG)
	{
		Util::DrawLine(getMiddlePosition(), getMiddlePosition() + getCurrentDirection() * getLOSDistance(), getLOSColour());
	}

	//for (int row = 0; row < m_tileList.size(); row++)
	//{
	//	for (int col = 0; col < m_tileList[0].size(); col++)
	//	{
	//		m_tileList[row][col].m_label.draw();
	//	}
	//}
}

void Player::update()
{
	handleEvent();
	Character::update();
	m_pWeapon->getTransform().getPosition() = getMiddlePosition() + getCurrentDirection() * 30.f;
	//std::cout << Util::signedAngle({ 0,-1 }, getCurrentDirection()) << std::endl;
	m_pWeapon->setCurrentHeading(Util::signedAngle({ 0,-1 }, getCurrentDirection()));

	moveToPath();
}

void Player::clean()
{
	delete m_pWeapon;
}

void Player::collision(DisplayObject* obj)
{

	if (obj->getType() == GameObjectType::ENEMY_ATTACK && !isHit())
	{
		takeDamage(dynamic_cast<AttackBox*>(obj)->getAttackPower());
		//dynamic_cast<AttackBox*>(obj)->deleteAttackBox();
		//std::cout << " aaa" << std::endl;
	}
	else if (obj->getType() == GameObjectType::ENEMY_RANGE_ATTACK)
	{
		if (!isHit())
		{
			takeDamage(dynamic_cast<RangeAttackBox*>(obj)->getPower());
		}
		getParent()->addChildRemoving(obj);
	}
}

void Player::hit()
{
	if (!m_isDead)
	{
		//m_curState = CharacterState::HIT;
		m_isHit = true;
		m_isAttacking = false;
		m_hitMotionNum = 20;
		//getRigidBody().getVelocity().x = 0;
	}
}

void Player::die()
{
	Character::die();
}

void Player::handleEvent()
{
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S) && EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
	moveToLeftDown();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S) && EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
	moveToRightDown();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W) && EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
	moveToRightUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W) && EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
	moveToLeftUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		moveToRight();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		moveToLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		moveToUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		moveToDown();
	}
	else
	{
		idle();
	}
	glm::vec2 mousePosition =  EventManager::Instance().getMousePosition();
	setCurrentDirection(Util::normalize(mousePosition - getMiddlePosition()));
	//std::cout << mousePosition.x << ", " << mousePosition.y << std::endl;
	if (EventManager::Instance().getMouseButton(static_cast<int>(MouseButtons::LEFT)))
	{
		if (!m_isLeftClick)
		{
			glm::vec2 attackPositionVec = getMiddlePosition() + getCurrentDirection() * 50.f;
			SDL_Rect attackPosition;
			attackPosition.x = attackPositionVec.x - 30;
			attackPosition.y = attackPositionVec.y - 30;
			attackPosition.w = 60;
			attackPosition.h = 60;
			getParent()->addChildDuringUpdating(new AttackBox(attackPosition, { 0,0 }, 0, GameObjectType::PLAYER_ATTACK, 50, getCurrentDirection().x < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
			SoundManager::Instance().playSound("attack");
			m_isLeftClick = true;
		}
	}
	else
	{
		m_isLeftClick = false;
	}

	if (EventManager::Instance().getMouseButton(static_cast<int>(MouseButtons::RIGHT)))
	{
		if (!m_isRightClick)
		{
			glm::vec2 position = getMiddlePosition() + getCurrentDirection() * 50.f;
			RangeAttackBox* attackBox = new RangeAttackBox(position.x - 20, position.y - 20, 40, 40, 20, GameObjectType::PLAYER_RANGE_ATTACK);
			attackBox->setCurrentHeading(Util::signedAngle({ 1,0 }, getCurrentDirection()));
			getParent()->addChildDuringUpdating(attackBox);
			SoundManager::Instance().playSound("fire");
			m_isRightClick = true;
		}
	}
	else
	{
		m_isRightClick = false;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_F))
	{
		//jump();

	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_Q))
	{
		//jump();
		//if (!m_isQEPushed)
		//{
		//	changeSwordLeft();
		//}
		//m_isQEPushed = true;
	}
	else
	{
		//m_isQEPushed = false;
	}
}

bool Player::getGameOver() const
{
	return m_gameOver;
}
