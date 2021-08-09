#pragma once
#ifndef __SOUND_ID__
#define __SOUND_ID__
#include <string>


class SoundID
{
public:
	inline static const std::string BGM =  "bgm";
	inline static const std::string HIT = "hit";
	inline static const std::string ATTACK = "attack";
	inline static const std::string JUMP = "jump";
	inline static const std::string ENEMY_EXPLOSION = "enemy_explosion";
	inline static const std::string ENEMY_MELEE_ATTACK = "enemy_melee_attack";

	inline static const std::string BTN_HOVER = "btn_hover";
	inline static const std::string BTN_CLICK = "btn_click";

};

#endif //__SOUND_ID__