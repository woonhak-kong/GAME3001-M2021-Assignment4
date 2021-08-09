#pragma once
#ifndef __TEXTURE_ID__
#define __TEXTURE_ID__
#include <string>


class TextureID
{
public:
	inline static const std::string ENEMY_HUMAN = "enemy_human";
	inline static const std::string ENEMY_HUMAN_IDLE = "enemy_human_idle";
	inline static const std::string ENEMY_HUMAN_ATTACK = "enemy_human_attack";
	inline static const std::string ENEMY_HUMAN_RUN = "enemy_human_run";
	inline static const std::string ENEMY_HUMAN_HIT = "enemy_human_hit";
	inline static const std::string ENEMY_HUMAN_FALL = "enemy_human_fall";
	inline static const std::string ENEMY_HUMAN_JUMP = "enemy_human_jump";
	inline static const std::string ENEMY_HUMAN_DEAD = "enemy_human_dead";
	inline static const std::string EXPLOSION1 = "explosion1";
	inline static const std::string EXPLOSION2 = "explosion2";
	inline static const std::string ENERGY_BACKGROUND = "energy_background";

	inline static const std::string BOSS1 = "boss1";
	inline static const std::string BOSS1_ATTACK1 = "boss1_attack1";
	inline static const std::string BOSS1_ATTACK2 = "boss1_attack2";
	inline static const std::string BOSS1_DEAD= "boss1_death";
	inline static const std::string BOSS1_FALL= "boss1_fall";
	inline static const std::string BOSS1_IDLE= "boss1_idle";
	inline static const std::string BOSS1_JUMP= "boss1_jump";
	inline static const std::string BOSS1_RUN= "boss1_run";
	inline static const std::string BOSS1_HIT = "boss1_hit";

	inline static const std::string DOOR = "door";
	inline static const std::string BASIC_SWORD = "basic_sword";
	inline static const std::string FIRE_SWORD = "fire_sword";
	inline static const std::string DARK_SWORD = "dark_sword";
	inline static const std::string LASER_SWORD = "laser_sword";

	inline static const std::string BOX = "box";

	inline static const std::string ATTACK_BOX = "attack_box";
	inline static const std::string SLASH_DARK = "slash_dark";
	inline static const std::string SLASH_FIRE = "slash_fire";
	inline static const std::string SLASH_LASER = "slash_laser";
	inline static const std::string SLASH_BASIC = "slash_basic";

	inline static const std::string HIT_PARTICLE = "hit_particle";
	inline static const std::string TRINKLE = "trinkle";

};

#endif //__TEXTURE_ID__