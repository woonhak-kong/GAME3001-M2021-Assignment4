#include "Character.h"

#include "Camera.h"
#include "CollisionManager.h"
#include "Config.h"
#include "Game.h"
#include "TextureManager.h"
#include "algorithm"
#include "AttackBox.h"

Character::Character(const LoaderParams& loader) :
	m_isJumping(false),
	m_isAttacking(false),
	m_isDead(false),
	m_isHit(false),
	m_isFlip(false),
	m_attackCollisionRect({0, 0, 0, 0}),
	m_moveSpeed(150),
	m_attackSpeed(1),
	m_curState(CharacterState::IDLE),
	m_attackType(GameObjectType::NONE),
	m_presentHp(loader.m_maxHp),
	m_maxHp(loader.m_maxHp),
	m_attackPower(loader.m_power),
	m_ai(nullptr),
	m_hitMotionNum(0),
	m_alpha(255),
	m_isDetectionRadius(false)
{
	getRigidBody().setMass(5);
	getRigidBody().getVelocity() = glm::vec2(0.0f, 0.0f);
	getRigidBody().getAcceleration() = glm::vec2(0.0f, 0.0f);
	getRigidBody().setColliding(false);
	getTransform().getPosition() = glm::vec2(loader.m_x, loader.m_y);
	setRealCollisionRect(loader.m_realWidth, loader.m_realHeight);
	setWidth(loader.m_widthOfTexture);
	setHeight(loader.m_heightOfTexture);
}

void Character::draw()
{
	PhysicsObject::draw();
	TextureManager::Instance().drawFillRect(getTransform().getPosition().x, getTransform().getPosition().y - 5, (static_cast<float>(m_presentHp) / static_cast<float>(m_maxHp)) * getWidth(), 5, { 255, 0, 0, 255 });
}

void Character::update()
{
	PhysicsObject::update();

	/*glm::vec2 previousPosition;
	glm::vec2 newPosition;*/

	// checking direction
	if (getRigidBody().getVelocity().x > 0)
	{
		m_isFlip = false;
	}
	else if (getRigidBody().getVelocity().x < 0)
	{
		m_isFlip = true;
	}


	// setting attackColiisonRect x, y
	if (m_isFlip)
	{
		// Left Direction
		m_attackCollisionRect.x = getRealCollisionRect().x - m_attackReach + getRealCollisionRect().w / 2;
		m_attackCollisionRect.y = getRealCollisionRect().y;

	}
	else
	{
		// Right Direction
		m_attackCollisionRect.x = getRealCollisionRect().x + getRealCollisionRect().w / 2;
		m_attackCollisionRect.y = getRealCollisionRect().y;
	}



	if (!m_isDead && m_presentHp <= 0)
	{
		die();
	}

	if (m_hitMotionNum > 0)
	{
		if (m_hitMotionNum % 2 == 0)
		{
			m_alpha = 20;
		}
		else
		{
			m_alpha = 255;
		}
		m_hitMotionNum--;
	}
	else
	{
		m_alpha = 255;
		m_isHit = false;
	}
}

void Character::clean()
{
	delete m_ai;
}

void Character::collision(DisplayObject* obj)
{
}

float Character::getMoveSpeed() const
{
	return m_moveSpeed;
}

float Character::getAttackSpeed() const
{
	return m_attackSpeed;
}

void Character::setAttackSpeed(float speed)
{
	m_attackSpeed = speed;
}

CharacterState Character::getCurrentState() const
{
	return m_curState;
}

bool Character::isFlip() const
{
	return m_isFlip;
}

bool Character::isAttacking() const
{
	return m_isAttacking;
}

bool Character::isDead() const
{
	return m_isDead;
}

bool Character::isHit() const
{
	return m_isHit;
}

SDL_Rect Character::getAttackCollisionRect() const
{
	return m_attackCollisionRect;
}

GameAI* Character::getGameAI() const
{
	return m_ai;
}

int Character::getPresentHp() const
{
	return m_presentHp;
}

int Character::getMaxHp() const
{
	return m_maxHp;
}

int Character::getAlpha() const
{
	return m_alpha;
}

bool Character::getDetectionRadius() const
{
	return m_isDetectionRadius;
}

void Character::setDetectionRadius(bool state)
{
	m_isDetectionRadius = state;
}


void Character::setMoveSpeed(float speed)
{
	m_moveSpeed = speed;
}

void Character::setCurrentState(CharacterState state)
{
	m_curState = state;
}

void Character::setAttackReach(int reach)
{
	m_attackReach = reach;
}

void Character::setAttackPower(int power)
{
	m_attackPower = power;
}

void Character::setAttackType(GameObjectType attackType)
{
	m_attackType = attackType;
}

void Character::setIsJumping(bool jumping)
{
	m_isJumping = jumping;
}

void Character::setAttackRectSize(int w, int h)
{
	m_attackCollisionRect.w = w;
	if (h == 0)
	{
		m_attackCollisionRect.h = getRealCollisionRect().h;
	}
	else
	{
		m_attackCollisionRect.h = h;
	}

}

glm::vec2 Character::getMiddlePosition()
{
	glm::vec2 middlePosition(getTransform().getPosition().x + getWidth() * 0.5f, getTransform().getPosition().y + getHeight() * 0.5f);
	return middlePosition;
}

void Character::setIsAttacking(bool attacking)
{
	m_isAttacking = attacking;
}

void Character::setIsDead(bool dead)
{
	m_isDead = dead;
}

void Character::setIsHit(bool hit)
{
	m_isHit = hit;
}

void Character::setGameAI(GameAI* ai)
{
	m_ai = ai;
}

void Character::takeDamage(int damage)
{
	if (!m_isDead)
	{
		m_presentHp = m_presentHp - damage;
		if (m_presentHp < 0)
		{
			m_presentHp = 0;
		}
		hit();
	}
}


void Character::jump()
{
	if (!m_isDead)
	{
		if (!m_isJumping && !m_isAttacking && !m_isHit)
		{
			getRigidBody().getVelocity().y = -(getRigidBody().getMass() * getFallingRate());
			m_isJumping = true;
			m_curState = CharacterState::JUMP;
		}
	}
}

void Character::moveToRight()
{
	if (!m_isDead)
	{
		if (m_isJumping)
		{
			getRigidBody().getVelocity().x = m_moveSpeed;
			getRigidBody().getVelocity().y = 0;
		}
		else
		{
			if (!m_isAttacking && !m_isHit)
			{
				getRigidBody().getVelocity().x = m_moveSpeed;
				getRigidBody().getVelocity().y = 0;
				m_curState = CharacterState::RUN;
			}
		}
	}
}

void Character::moveToLeft()
{
	if (!m_isDead)
	{
		if (m_isJumping)
		{
			getRigidBody().getVelocity().x = -m_moveSpeed;
			getRigidBody().getVelocity().y = 0;
		}
		else
		{
			if (!m_isAttacking && !m_isHit)
			{
				getRigidBody().getVelocity().x = -m_moveSpeed;
				getRigidBody().getVelocity().y = 0;
				m_curState = CharacterState::RUN;
			}
		}
	}
}

void Character::moveToUp()
{
	if (!m_isDead)
	{
		if (m_isJumping)
		{
			getRigidBody().getVelocity().y = -m_moveSpeed;
			getRigidBody().getVelocity().x = 0;
		}
		else
		{
			if (!m_isAttacking && !m_isHit)
			{
				getRigidBody().getVelocity().y = -m_moveSpeed;
				getRigidBody().getVelocity().x = 0;
				m_curState = CharacterState::RUN;
			}
		}
	}
}

void Character::moveToDown()
{
	if (!m_isDead)
	{
		if (m_isJumping)
		{
			getRigidBody().getVelocity().y = +m_moveSpeed;
			getRigidBody().getVelocity().x = 0;
		}
		else
		{
			if (!m_isAttacking && !m_isHit)
			{
				getRigidBody().getVelocity().y = +m_moveSpeed;
				getRigidBody().getVelocity().x = 0;
				m_curState = CharacterState::RUN;
			}
		}
	}
}

void Character::moveToRightUp()
{
	if (!m_isDead)
	{
		if (!m_isAttacking && !m_isHit)
		{
			getRigidBody().getVelocity().x = +m_moveSpeed;
			getRigidBody().getVelocity().y = -m_moveSpeed;

			m_curState = CharacterState::RUN;
		}
	}
}

void Character::moveToLeftUp()
{
	if (!m_isDead)
	{
		if (!m_isAttacking && !m_isHit)
		{
			getRigidBody().getVelocity().x = -m_moveSpeed;
			getRigidBody().getVelocity().y = -m_moveSpeed;

			m_curState = CharacterState::RUN;
		}
	}
}

void Character::moveToRightDown()
{
	if (!m_isDead)
	{
		if (!m_isAttacking && !m_isHit)
		{
			getRigidBody().getVelocity().x = +m_moveSpeed;
			getRigidBody().getVelocity().y = +m_moveSpeed;

			m_curState = CharacterState::RUN;
		}
	}
}

void Character::moveToLeftDown()
{
	if (!m_isDead)
	{
		if (!m_isAttacking && !m_isHit)
		{
			getRigidBody().getVelocity().x = -m_moveSpeed;
			getRigidBody().getVelocity().y = +m_moveSpeed;

			m_curState = CharacterState::RUN;
		}
	}
}

void Character::idle()
{
	if (!m_isDead)
	{
		getRigidBody().getVelocity().x = 0;
		getRigidBody().getVelocity().y = 0;
		if (!m_isJumping && !m_isAttacking && !m_isHit)
		{
			m_curState = CharacterState::IDLE;
		}
	}
}

void Character::attack()
{
	if (!m_isDead)
	{
		if (!m_isAttacking && !m_isHit)
		{
			m_curState = CharacterState::ATTACK;
			m_isAttacking = true;
			if (!m_isJumping)
			{
				getRigidBody().getVelocity().x = 0;
			}
		}
	}
}

void Character::hit()
{
	if (!m_isDead)
	{
		//m_curState = CharacterState::HIT;
		m_isHit = true;
		m_isAttacking = false;
		m_hitMotionNum = 20;
		getRigidBody().getVelocity().x = 0;
	}
}

void Character::die()
{
	m_curState = CharacterState::DEAD;
	m_isDead = true;
	//getParent()->addChildRemoving(this);
}

void Character::makingAttackCollisionBox(SwordType type /* = SwordType::NONE */)
{
	getParent()->addChildDuringUpdating(new AttackBox(m_attackCollisionRect, glm::vec2(m_isFlip ? getAttackSpeed() * -10 : getAttackSpeed() * 10, 0), m_attackReach, m_attackType, m_attackPower, m_isFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, type));
}
