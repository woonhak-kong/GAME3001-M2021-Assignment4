#include "EnemyHuman1.h"

#include "AttackBox.h"
#include "CallbackType.h"
#include "Camera.h"
#include "Config.h"
#include "EnemyHumanAI.h"
#include "Explosion.h"
#include "RangeAttackBox.h"
#include "Scene.h"
#include "ScoreManager.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "Sword.h"
#include "TextureID.h"
#include "TextureManager.h"
#include "Util.h"

EnemyHuman1::EnemyHuman1(const LoaderParams& loader) :
	Character(loader),
	m_pWeapon(nullptr)
{

	Animation animation = Animation();
	Frame frame;
	glm::vec2 size;
	std::string animationName = "monster1";

	TextureManager::Instance().load("assets/characters/monster/zimbie_idle.png", "zombie_idle");
	TextureManager::Instance().load("assets/characters/monster/zimbie_run.png", "zombie_run");
	size = glm::vec2(32, 34);

	animation.name = "zombie_idle";
	for (int i = 0; i < 4; ++i)
	{
		frame.name = "zombie_idle";
		frame.x = size.x * i;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	animation.name = "zombie_run";
	for (int i = 0; i < 4; ++i)
	{
		frame.name = "zombie_run";
		frame.x = size.x * i;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	setAnimation(TextureManager::Instance().getAnimation("monster1"));

	// todo make it automatic
	setType(GameObjectType::ENEMY);
	setAttackType(GameObjectType::ENEMY_ATTACK);
	setGameAI(new EnemyHumanAI(this));
	//////////////////////////////////////
	///
	setAttackSpeed(2);
	setAttackReach(50);
	setAttackRectSize(50, 0);
	m_pWeapon = new Weapon(WeaponType::SWORD1);
	setLOSDistance(300.f);
	m_pWeapon->setCurrentHeading(0.f);
	setCurrentDirection({1,0});
}

EnemyHuman1::~EnemyHuman1()
{
}

void EnemyHuman1::draw()
{
	Character::draw();
	/*TextureManager::Instance().draw("napkin", getTransform().getPosition().x - Camera::Instance().getPosition().x,
		getTransform().getPosition().y - Camera::Instance().getPosition().y , getWidth(), getHeight(),  0, 255);*/
	SDL_RendererFlip flip;
	flip = isFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	switch (getCurrentState())
	{
		case CharacterState::IDLE:
			TextureManager::Instance().playAnimation(getAnimation("zombie_idle"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, getAlpha(), flip);
			break;
		case CharacterState::ATTACK:

			break;
		case CharacterState::RUN:
			TextureManager::Instance().playAnimation(getAnimation("zombie_run"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, getAlpha(), flip);
			break;
		case CharacterState::JUMP:
			break;
		case CharacterState::FALL:
			break;
		case CharacterState::HIT:
			break;
		case CharacterState::DEAD:
			TextureManager::Instance().playAnimation(getAnimation("zombie_idle"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.4f, 0.0f, 255, flip, false, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ANIMATION_END:
							//std::cout << "die call back" << std::endl;
							ScoreManager::addScore(10);
							getParent()->addChildDuringUpdating(new Explosion(getTransform().getPosition().x-10, getTransform().getPosition().y-10, getWidth()+20, getWidth()+20, ExplosionType::EXPLOSION_SMALL));
							//getParent()->addChildDuringUpdating(new Sword(getRealCollisionRect().x, getRealCollisionRect().y, static_cast<SwordType>(rand() % 3 + 1)));
							getParent()->addChildRemoving(this);
							break;
						default:
							break;
					}
				});

			break;
	}

	m_pWeapon->draw();
	if (Config::SHOWING_DEBUG)
	{
		Util::DrawLine(getMiddlePosition(), getMiddlePosition() + getCurrentDirection() * getLOSDistance(), getLOSColour());
		if (getDetectionRadius())
		{
			Util::DrawCircle(getCenterPosition(), getLOSDistance(), {1, 0, 0, 1});
		}
		else
		{
			Util::DrawCircle(getCenterPosition(),getLOSDistance());
		}

	}
}

void EnemyHuman1::update()
{
	Character::update();
	getGameAI()->update();
	m_pWeapon->getTransform().getPosition() = getMiddlePosition() + getCurrentDirection() * 30.f;
	//std::cout << Util::signedAngle({ 0,-1 }, getCurrentDirection()) << std::endl;
	m_pWeapon->setCurrentHeading(Util::signedAngle({ 0,-1 }, getCurrentDirection()));
}

void EnemyHuman1::clean()
{

}

void EnemyHuman1::collision(DisplayObject* obj)
{
	if (obj->getType() == GameObjectType::PLAYER_ATTACK && !isHit())
	{
		takeDamage(dynamic_cast<AttackBox*>(obj)->getAttackPower());
		//dynamic_cast<AttackBox*>(obj)->deleteAttackBox();
		//std::cout << " aaa" << std::endl;
	}
	else if (obj->getType() == GameObjectType::PLAYER_RANGE_ATTACK)
	{
		if (!isHit())
		{
			takeDamage(dynamic_cast<RangeAttackBox*>(obj)->getPower());
		}
		getParent()->addChildRemoving(obj);
	}
}

void EnemyHuman1::hit()
{
	if (!isHit())
	{
		SoundManager::Instance().playSound(SoundID::HIT);
	}
	Character::hit();
}

void EnemyHuman1::die()
{

	Character::die();
}
