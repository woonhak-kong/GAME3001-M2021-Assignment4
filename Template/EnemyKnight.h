#pragma once
#include "Character.h"
class EnemyKnight : public Character
{
public:
	EnemyKnight(const LoaderParams& loader);
	virtual ~EnemyKnight() = default;

	void draw() override;
	void update() override;
	void clean() override;

	void handleEvent();
};

