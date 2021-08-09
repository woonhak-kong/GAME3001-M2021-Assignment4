#pragma once
#ifndef __LOADER_PARAMS__
#define __LOADER_PARAMS__
#include <string>

class LoaderParams
{
public:
	LoaderParams(int x, int y, int widthOfTexture, int heightOfTexture, int realWidth, int realHeight, int maxHp, int power, std::string textureID) :
		m_x(x),
		m_y(y),
		m_widthOfTexture(widthOfTexture),
		m_heightOfTexture(heightOfTexture),
		m_realWidth(realWidth),
		m_realHeight(realHeight),
		m_maxHp(maxHp),
		m_power(power),
		m_id(textureID)
	{}



	int m_x;
	int m_y;
	int m_widthOfTexture;
	int m_heightOfTexture;
	int m_realWidth;
	int m_realHeight;
	int m_maxHp;
	int m_power;
	std::string m_id;



};


#endif //__LOADER_PARAMS__