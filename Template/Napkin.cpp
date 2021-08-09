#include "Napkin.h"

#include <iostream>

#include "AttackBox.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "Config.h"
#include "EventManager.h"
#include "Game.h"
#include "Scene.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "TextureID.h"
#include "TextureManager.h"

Napkin::Napkin(const LoaderParams& loader) :
	Character(loader),
	m_energyBar(nullptr),
	m_swordDurability(nullptr),
	m_gameOver(false),
	m_gameClear(false),
	m_jumpNum(0),
	m_isJumpPushed(false),
	m_isQEPushed(false),
	m_hitMotionNum(0),
	m_swordIdx(0)
{

	//todo / we should control load function XML
	Animation animation = Animation();
	Frame frame;
	glm::vec2 size;
	std::string animationName = "napkin";

	TextureManager::Instance().load("assets/characters/player/idle/adventurer-idle-2-00.png", "idle0");
	TextureManager::Instance().load("assets/characters/player/idle/adventurer-idle-2-01.png", "idle1");
	TextureManager::Instance().load("assets/characters/player/idle/adventurer-idle-2-02.png", "idle2");
	TextureManager::Instance().load("assets/characters/player/idle/adventurer-idle-2-03.png", "idle3");
	size = TextureManager::Instance().getTextureSize("idle0");

	animation.name = "idle";
	for (int i = 0; i < 4; ++i)
	{
		frame.name = "idle" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack1-00-1.3.png", "attack1_0");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack1-01-1.3.png", "attack1_1");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack1-02-1.3.png", "attack1_2");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack1-03-1.3.png", "attack1_3");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack1-04-1.3.png", "attack1_4");

	animation.name = "attack1";
	for (int i = 0; i < 5; ++i)
	{
		frame.name = "attack1_" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-00-1.3.png", "attack2_0");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-01-1.3.png", "attack2_1");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-02-1.3.png", "attack2_2");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-03-1.3.png", "attack2_3");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-04-1.3.png", "attack2_4");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack2-05-1.3.png", "attack2_5");

	animation.name = "attack2";
	for (int i = 0; i < 6; ++i)
	{
		frame.name = "attack2_" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-00-1.3.png", "attack3_0");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-01-1.3.png", "attack3_1");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-02-1.3.png", "attack3_2");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-03-1.3.png", "attack3_3");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-04-1.3.png", "attack3_4");
	TextureManager::Instance().load("assets/characters/player/attack/adventurer-attack3-05-1.3.png", "attack3_5");

	animation.name = "attack3";
	for (int i = 0; i < 6; ++i)
	{
		frame.name = "attack3_" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-00.png", "run0");
	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-01.png", "run1");
	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-02.png", "run2");
	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-03.png", "run3");
	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-04.png", "run4");
	TextureManager::Instance().load("assets/characters/player/run/adventurer-run3-05.png", "run5");

	animation.name = "run";
	for (int i = 0; i < 6; ++i)
	{
		frame.name = "run" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	TextureManager::Instance().load("assets/characters/player/jump/adventurer-jump-00.png", "jump0");
	TextureManager::Instance().load("assets/characters/player/jump/adventurer-jump-01.png", "jump1");
	TextureManager::Instance().load("assets/characters/player/jump/adventurer-jump-02.png", "jump2");
	TextureManager::Instance().load("assets/characters/player/jump/adventurer-jump-03.png", "jump3");

	animation.name = "jump";
	for (int i = 0; i < 4; ++i)
	{
		frame.name = "jump" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();


	TextureManager::Instance().load("assets/characters/player/fall/adventurer-fall-00.png", "fall0");
	TextureManager::Instance().load("assets/characters/player/fall/adventurer-fall-01.png", "fall1");

	animation.name = "fall";
	for (int i = 0; i < 2; ++i)
	{
		frame.name = "fall" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	// dead
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-00.png", "die0");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-01.png", "die1");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-02.png", "die2");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-03.png", "die3");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-04.png", "die4");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-05.png", "die5");
	TextureManager::Instance().load("assets/characters/player/die/adventurer-knock-dwn-06.png", "die6");


	animation.name = "die";
	for (int i = 0; i < 7; ++i)
	{
		frame.name = "die" + std::to_string(i);
		frame.x = 0;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	setAnimation(TextureManager::Instance().getAnimation("napkin"));




	// todo
	// when character is created, must to be set.
	setType(GameObjectType::PLAYER);
	setAttackType(GameObjectType::PLAYER_ATTACK);
	/////////////////////////////////////////////////


	m_swordVector.push_back(new Sword(Config::SCREEN_WIDTH * 0.5 - 30, 30, SwordType::BASIC_SWORD));
	m_setSwordProperty();
	m_swordVector[m_swordIdx]->setWidth(60);
	m_swordVector[m_swordIdx]->setHeight(60);
	//setAttackSpeed(2);
	//setAttackReach(100);
	/*std::cout << getAnimation("attack2").frames.size()<< std::endl;
	setAttackSpeed(getAnimation("attack2").frames.size()* round(getAnimation("attack2").frames.size() / 2 / 0.5f));*/

	// only player can have Camera.
	Camera::Instance().setTarget(&getTransform().getPosition());

	//UI
	m_energyBar = new EnergyBar(loader.m_maxHp);
	m_swordDurability = new Label("[00/00]", "Consolas", 13, { 0, 255, 0, 255 },
		glm::vec2(Config::SCREEN_WIDTH * 0.5 - 5, 85), 0, false);

}

Napkin::~Napkin()
{

}

void Napkin::draw()
{
	Character::draw();
	/*TextureManager::Instance().draw("napkin", getTransform().getPosition().x - Camera::Instance().getPosition().x,
		getTransform().getPosition().y - Camera::Instance().getPosition().y , getWidth(), getHeight(),  0, 255);*/
	int alpha;
	if (m_hitMotionNum > 0)
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
	}
	SDL_RendererFlip flip;
	flip = isFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	switch (getCurrentState())
	{
		case CharacterState::IDLE:
			TextureManager::Instance().playAnimation(getAnimation("idle"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, alpha, flip);

			break;
		case CharacterState::ATTACK:
			TextureManager::Instance().playAnimation(getAnimation("attack2"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), getAttackSpeed(), 0.0f, alpha, flip, true, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ATTACK_BOX:
							this->makingAttackCollisionBox(m_swordVector[m_swordIdx]->getSwordType());
							break;
						case CallbackType::ANIMATION_END:
							this->setIsAttacking(false);
							break;
						default:
							break;
					}
				},3);
			break;
		case CharacterState::RUN:
			TextureManager::Instance().playAnimation(getAnimation("run"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, alpha, flip);
			break;
		case CharacterState::JUMP:
			TextureManager::Instance().playAnimation(getAnimation("jump"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, alpha, flip );
			break;
		case CharacterState::FALL:
			TextureManager::Instance().playAnimation(getAnimation("fall"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, alpha, flip);
			break;
		case CharacterState::DEAD:
			TextureManager::Instance().playAnimation(getAnimation("die"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, alpha, flip, false, [&](CallbackType type) -> void
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

	//Sword
	m_swordVector[m_swordIdx]->drawUi();

	//UI
	m_energyBar->draw();
	TextureManager::Instance().draw(TextureID::BOX, Config::SCREEN_WIDTH * 0.5 - 60, 5, 120, 120);
	TextureManager::Instance().draw(TextureID::BOX, Config::SCREEN_WIDTH * 0.5 - 120, 125 - 50, 50, 50);
	TextureManager::Instance().draw(TextureID::BOX, Config::SCREEN_WIDTH * 0.5 + 70, 125 - 50, 50, 50);
	if (m_swordVector.size() > 1)
	{
		int left = m_swordIdx - 1;
		if (left < 0)
		{
			left = m_swordVector.size() - 1;
		}
		int right = m_swordIdx + 1;
		if (right >= m_swordVector.size())
		{
			right = 0;
		}
		switch (m_swordVector[left]->getSwordType())
		{
			case SwordType::BASIC_SWORD:
				TextureManager::Instance().draw(TextureID::BASIC_SWORD, Config::SCREEN_WIDTH * 0.5 - 110, 125 - 40, 30, 30);
				break;
			case SwordType::FIRE_SWORD:
				TextureManager::Instance().draw(TextureID::FIRE_SWORD, Config::SCREEN_WIDTH * 0.5 - 110, 125 - 40, 30, 30);
				break;
			case SwordType::LASER_SWORD:
				TextureManager::Instance().draw(TextureID::LASER_SWORD, Config::SCREEN_WIDTH * 0.5 - 110, 125 - 40, 30, 30);
				break;
			case SwordType::DARK_SWORD:
				TextureManager::Instance().draw(TextureID::DARK_SWORD, Config::SCREEN_WIDTH * 0.5 - 110, 125 - 40, 30, 30);
				break;
		}
		switch (m_swordVector[right]->getSwordType())
		{
			case SwordType::BASIC_SWORD:
				TextureManager::Instance().draw(TextureID::BASIC_SWORD, Config::SCREEN_WIDTH * 0.5 + 80, 125 - 40, 30, 30);
				break;
			case SwordType::FIRE_SWORD:
				TextureManager::Instance().draw(TextureID::FIRE_SWORD, Config::SCREEN_WIDTH * 0.5 + 80, 125 - 40, 30, 30);
				break;
			case SwordType::LASER_SWORD:
				TextureManager::Instance().draw(TextureID::LASER_SWORD, Config::SCREEN_WIDTH * 0.5 + 80, 125 - 40, 30, 30);
				break;
			case SwordType::DARK_SWORD:
				TextureManager::Instance().draw(TextureID::DARK_SWORD, Config::SCREEN_WIDTH * 0.5 + 80, 125 - 40, 30, 30);
				break;
		}
	}
	m_swordDurability->draw();


}

void Napkin::update()
{
	handleEvent();
	Character::update();
	if (getRigidBody().getVelocity().y >= 0)
	{
		if (isOnGround())
		{
			m_jumpNum = 0;
		}
	}
	if (m_swordVector[m_swordIdx]->getSwordType() == SwordType::BASIC_SWORD)
	{
		m_swordDurability->setText("Infinity");
	}
	else
	{
		m_swordDurability->setText(std::to_string(m_swordVector[m_swordIdx]->getDurability()) + "/" + std::to_string(m_swordVector[m_swordIdx]->getMaxDrability()));
	}

}

void Napkin::clean()
{
	delete m_energyBar;
}

void Napkin::hit()
{
	m_energyBar->setEnergy(getPresentHp());
	m_hitMotionNum = 20;
}

void Napkin::collision(DisplayObject* obj)
{
	if (obj->getType() == GameObjectType::ENEMY_ATTACK)
	{
		takeDamage(dynamic_cast<AttackBox*>(obj)->getAttackPower());
		dynamic_cast<AttackBox*>(obj)->deleteAttackBox();
	}
	if (obj->getType() == GameObjectType::DOOR)
	{
		//obj->setEnabled(false);
		m_gameClear = true;
	}
	if (obj->getType() == GameObjectType::SWORD)
	{
		bool sameSword = false;
		for (auto& sword : m_swordVector)
		{
			if (dynamic_cast<Sword*>(obj)->getSwordType() == sword->getSwordType())
			{
				sword->setDurability(sword->getMaxDrability());
				getParent()->addChildRemoving(obj);
				sameSword = true;
				break;
			}
		}
		if (!sameSword)
		{
			m_swordVector.push_back(dynamic_cast<Sword*>(obj));
			getParent()->removeFromListExceptDeleting(obj);
			m_setSwordUI();
			changeSwordRight();
		}
	}

}

void Napkin::die()
{
	Character::die();
}

void Napkin::handleEvent()
{
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_RIGHT))
	{
		moveToRight();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_LEFT))
	{
		moveToLeft();
	}
	else
	{
		idle();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		//jump();
		if (!m_isJumpPushed)
		{

			if (getCurrentState() == CharacterState::FALL && m_jumpNum == 0)
			{
				setIsJumping(false);
				m_jumpNum = 2;
				jump();
				SoundManager::Instance().playSound(SoundID::JUMP);

			}
			else if (m_jumpNum == 0)
			{
				m_jumpNum++;
				jump();
				SoundManager::Instance().playSound(SoundID::JUMP);
			}
			else if (m_jumpNum == 1)
			{
				setIsJumping(false);
				m_jumpNum++;
				jump();
				SoundManager::Instance().playSound(SoundID::JUMP);
			}
		}
		m_isJumpPushed = true;
	}
	else
	{
		m_isJumpPushed = false;
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_F))
	{
		if (!isDead() && !isAttacking())
		{
			int durability = m_swordVector[m_swordIdx]->getDurability();
			m_swordVector[m_swordIdx]->setDurability(--durability);
			SoundManager::Instance().playSound(SoundID::ATTACK);
			attack();
			if (m_swordVector[m_swordIdx]->getSwordType() != SwordType::BASIC_SWORD && m_swordVector[m_swordIdx]->getDurability() <= 0)
			{
				m_removeZeroDurabilitySword();
			}
		}

	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_Q))
	{
		//jump();
		if (!m_isQEPushed)
		{
			changeSwordLeft();
		}
		m_isQEPushed = true;
    }
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_E))
	{
		//jump();
		if (!m_isQEPushed)
		{
			changeSwordRight();
		}

		m_isQEPushed = true;
	}
	else
	{
		m_isQEPushed = false;
	}

}

void Napkin::changeSwordRight()
{
	m_swordIdx++;
	if (m_swordIdx >= m_swordVector.size())
	{
		m_swordIdx = 0;
	}
	m_setSwordProperty();
}

void Napkin::changeSwordLeft()
{
	m_swordIdx--;
	if (m_swordIdx < 0)
	{
		m_swordIdx = m_swordVector.size() - 1;
	}
	m_setSwordProperty();
}

bool Napkin::getGameOver() const
{
	return m_gameOver;
}

bool Napkin::getGameClear() const
{
	return m_gameClear;
}

void Napkin::cleanSword()
{
	for (auto& sword : m_swordVector)
	{
		delete sword;
		sword = nullptr;
	}
	m_swordVector.clear();
}

void Napkin::m_setSwordUI()
{
	m_swordVector.back()->getTransform().getPosition() = { Config::SCREEN_WIDTH * 0.5 - 30, 30 };
	setAttackSpeed(m_swordVector.back()->getAttackSpeed());
	setAttackReach(m_swordVector.back()->getReach());
	setAttackPower(m_swordVector.back()->getPower());
	m_swordVector.back()->setWidth(60);
	m_swordVector.back()->setHeight(60);
}

void Napkin::m_removeZeroDurabilitySword()
{
	delete m_swordVector[m_swordIdx];
	m_swordVector[m_swordIdx] = nullptr;
	m_swordVector.erase(std::remove(m_swordVector.begin(), m_swordVector.end(), m_swordVector[m_swordIdx]), m_swordVector.end());
	changeSwordLeft();
}

void Napkin::m_setSwordProperty()
{
	setAttackSpeed(m_swordVector[m_swordIdx]->getAttackSpeed());
	setAttackReach(m_swordVector[m_swordIdx]->getReach());
	setAttackPower(m_swordVector[m_swordIdx]->getPower());
	setAttackRectSize(m_swordVector[m_swordIdx]->getReach(), 0);
}
