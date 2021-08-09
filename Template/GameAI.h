#pragma once
#ifndef __GAME_AI__
#define __GAME_AI__


class GameAI
{
public:
	friend class Character;
	GameAI(Character* character) : m_self(character) {}
	virtual ~GameAI() = default;
	virtual void update() = 0;


protected:
	Character* m_self;

};




#endif// __GAME_AI__
