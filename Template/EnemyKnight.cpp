#include "EnemyKnight.h"

#include <iostream>

#include "Camera.h"
#include "KnightAI.h"
#include "TextureManager.h"

EnemyKnight::EnemyKnight(const LoaderParams& loader) :
	Character(loader)
{
	Animation animation = Animation();
	Frame frame;
	glm::vec2 size;

	TextureManager::Instance().load("assets/characters/enemy/knight/knight_idle.png", "knight_idle0");

	size = TextureManager::Instance().getTextureSize("knight_idle0");

	animation.name = "knight_idle";

	std::cout << size.x / size.y << std::endl;
	for (int i = 0; i < (size.x / size.y); ++i)
	{
		frame.name = "knight_idle0";
		frame.x = i * size.y;
		frame.y = 0;
		frame.w = size.y;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation("knight_idle", animation);

	setAnimation(TextureManager::Instance().getAnimation("knight_idle"));

	animation.frames.clear();


	// todo make it automatic
	setType(GameObjectType::ENEMY);
	setGameAI(new KnightAI(this));
	//////////////////////////////////////

}

void EnemyKnight::draw()
{
	Character::draw();
	/*TextureManager::Instance().draw("napkin", getTransform().getPosition().x - Camera::Instance().getPosition().x,
		getTransform().getPosition().y - Camera::Instance().getPosition().y , getWidth(), getHeight(),  0, 255);*/
	SDL_RendererFlip flip;
	flip = isFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	switch (getCurrentState())
	{
		case CharacterState::IDLE:
			TextureManager::Instance().playAnimation(getAnimation("knight_idle"), getTransform().getPosition().x - Camera::Instance().getPosition().x,
				getTransform().getPosition().y - Camera::Instance().getPosition().y, getWidth(), getHeight(), 0.5f, 0.0f, 255, flip);

			break;
		case CharacterState::ATTACK:
			break;
		case CharacterState::RUN:
			break;
		case CharacterState::JUMP:
			break;
		case CharacterState::FALL:
			break;
		case CharacterState::DEAD:

			break;
	}

}

void EnemyKnight::update()
{
	Character::update();
	handleEvent();
}

void EnemyKnight::clean()
{
}

void EnemyKnight::handleEvent()
{
	getGameAI()->update();
}
