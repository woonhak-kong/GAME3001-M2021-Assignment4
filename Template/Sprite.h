#pragma once
#ifndef __SPRITE__
#define __SPRITE__

#include "DisplayObject.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include <unordered_map>

class Sprite : public DisplayObject
{
public:
	Sprite();
	virtual ~Sprite() = default;
	virtual void draw()  = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	void collision(DisplayObject* obj) override;
	// getters
	SpriteSheet* getSpriteSheet();
	Animation& getAnimation(const std::string& state);

	// setters
	void setSpriteSheet(SpriteSheet* sprite_sheet);
	void setAnimation(std::unordered_map<std::string, Animation> animation);
private:
	// private utility functions
	//bool m_animationExists(const std::string& id);

	SpriteSheet* m_pSpriteSheet;

	std::unordered_map<std::string, Animation> m_pAnimations;

};

#endif //__SPRITE__
