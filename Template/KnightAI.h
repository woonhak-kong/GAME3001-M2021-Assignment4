#pragma once
#ifndef __KNIGHT_AI__
#define __KNIGHT_AI__

#include "GameAI.h"
//#include "Character.h"

class Character;
class KnightAI : public GameAI
{
public:
	KnightAI(Character* character);
	~KnightAI() = default;
	void update() override;


};

#endif //__KNIGHT_AI__