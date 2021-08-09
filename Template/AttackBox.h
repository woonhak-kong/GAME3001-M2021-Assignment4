#pragma once
#include "Sprite.h"
#include "SwordType.h"

class AttackBox : public Sprite
{
public:
	AttackBox(SDL_Rect rect, glm::vec2 velocity, int distance, GameObjectType attackType, int power, SDL_RendererFlip flip, SwordType type = SwordType::BASIC_SWORD);
	virtual ~AttackBox();
	void draw() override;
	void update() override;
	void clean() override;
	void collision(DisplayObject* obj) override;
	int getAttackPower() const;
	void deleteAttackBox();

private:

	int m_power;
	int m_distance4Delete;
	int m_startingPoint;
	bool m_isDeleted;
	SwordType m_type;
	SDL_RendererFlip m_flip;

};

