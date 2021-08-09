#include "FontManager.h"

#include "Game.h"
#include "TextureManager.h"

inline bool FontManager::m_exists(const std::string& id)
{
	return m_fontMap.find(id) != m_fontMap.end();
}

bool FontManager::load(const std::string& file_name, const std::string& id, const int size, const int style)
{
	if (m_exists(id))
	{
		return true;
	}

	TTF_Font* font = TTF_OpenFont(file_name.c_str(), size);
	if (font != nullptr)
	{
		TTF_SetFontStyle(font, style);
		m_fontMap[id] = font;
		return true;
	}

	return false;
}

bool FontManager::textToTexture(const std::string& text, const std::string& font_id, const std::string& texture_id, const SDL_Color colour)
{
	//Render text surface

	SDL_Surface* textSurface = TTF_RenderText_Solid(m_fontMap[font_id], text.c_str(), colour);

	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(/* TheGame::Instance()->getRenderer()*/ TextureManager::Instance().getRenderer(), textSurface);

		SDL_FreeSurface(textSurface);

		//Create texture from surface pixels
		//if(TextureManager::Instance().getTexture(texture_id) != nullptr)
		//{
			TextureManager::Instance().removeTexture(texture_id);
		//}
		TextureManager::Instance().addTexture(texture_id, pTexture);
		if (TextureManager::Instance().getTexture(texture_id) == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return false;
		}
	}

	return true;
}

TTF_Font* FontManager::getFont(const std::string& id)
{
	return m_fontMap[id];
}

void FontManager::clean()
{
	for(auto iter = m_fontMap.begin(); iter != m_fontMap.end(); iter++)
	{
		TTF_CloseFont(iter->second);
	}
	m_fontMap.clear();
}

void FontManager::displayFontMap()
{
	std::cout << "------------ Displaying Font Map -----------" << std::endl;

	std::cout << "Font Map size: " << m_fontMap.size() << std::endl;

	auto it = m_fontMap.begin();
	while (it != m_fontMap.end())
	{
		std::cout << " " << it->first << std::endl;
		++it;
	}
}