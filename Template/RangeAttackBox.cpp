#include "RangeAttackBox.h"

#include "Camera.h"
#include "CollisionManager.h"
#include "Game.h"
#include "TextureManager.h"

RangeAttackBox::RangeAttackBox(int x, int y, int w, int h, int power, GameObjectType attackType)
{
	setType(attackType);
	Animation animation = Animation();
	Frame frame;
	glm::vec2 size;
	std::string animationName = "arrow1";

	TextureManager::Instance().load("assets/particles/arrow1.png", "arrow1");
	size = glm::vec2(100, 100);

	animation.name = "arrow1";
	for (int i = 0; i < 30; ++i)
	{
		frame.name = "arrow1";
		frame.x = size.x * i;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();
	setAnimation(TextureManager::Instance().getAnimation("arrow1"));


	m_power = power;
	getTransform().getPosition().x = x;
	getTransform().getPosition().y = y;
	setWidth(w);
	setHeight(h);
	setRealCollisionRect(w - 20, h - 20);
}

RangeAttackBox::~RangeAttackBox()
{
}

void RangeAttackBox::draw()
{
	TextureManager::Instance().playAnimation(getAnimation("arrow1"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
		getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 4.f, getCurrentHeading(), 255, SDL_FLIP_NONE, true, [&](CallbackType type) -> void
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
		});
}

void RangeAttackBox::update()
{
	getTransform().getPosition() = getTransform().getPosition() + getCurrentDirection() * (Game::Instance().getDeltaTime() * 300);
	if (CollisionManager::checkCollideTile4Missile({ getRealCollisionRect().x,getRealCollisionRect().y, getRealCollisionRect().w, getRealCollisionRect().h }, getParent()->getNodeList()))
	{
		getParent()->addChildRemoving(this);
	}
}

void RangeAttackBox::clean()
{
}

void RangeAttackBox::collision(DisplayObject* obj)
{
}

int RangeAttackBox::getPower() const
{
	return m_power;
}
