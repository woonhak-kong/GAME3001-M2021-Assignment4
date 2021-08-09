#pragma once
#ifndef __CONFIG__
#define __CONFIG__

#include <SDL_ttf.h>
#include <memory>
#include <string>

#include "glm/vec2.hpp"

class Config {
public:
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;
	static const int ROW_NUM = 15;
	static const int COL_NUM = 20;
	static const int TILE_SIZE = 40;
	static const int TILE_COST = 1;
	static const int MINE_NUM = 50;
	static const int SCORE = 0;
	static const int LIVES = 5;
	static const int GRAVITY = 5.0f;
	inline static bool SHOWING_DEBUG = true;
	inline static int mapWidth = 0;
	inline static int mapHeight = 0;

	// about texture
	inline static const std::string TEXTURE_LOCATION = "assets/state.xml";

	inline static const std::string SCENE0_LOCATION = "assets/maps/scene0.tmx";
	inline static const std::string SCENE1_LOCATION = "assets/maps/scene1.tmx";

	inline static const std::string TUTORIAL_SCENE = "TUTORIALSCENE";
	inline static const std::string START_SCENE = "STARTSCENE";
	inline static const std::string END_SCENE = "ENDSCENE";
	inline static const std::string PLAY_SCENE1 = "PLAYSCENE1";
	inline static const std::string PLAY_SCENE2 = "PLAYSCENE2";
	inline static const std::string PLAY_SCENE3 = "PLAYSCENE3";

};

#endif /* defined (__CONFIG__) */