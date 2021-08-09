#pragma once
#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

// Core Libraries
#include <string>
#include <unordered_map>

#include "glm/vec2.hpp"

// SDL Libraries
#include <functional>
#include<SDL.h>

#include "SpriteSheet.h"
#include "Animation.h"
#include "CallbackType.h"

/* Singleton */
class TextureManager
{
public:
	static TextureManager& Instance()
	{
		static TextureManager instance;
		return instance;
	}

	// loading functions
	bool load(const std::string& file_name, const std::string& id);
	bool loadSpriteSheet(const std::string& data_file_name, const std::string& texture_file_name, const std::string& sprite_sheet_name);

	// drawing functions
	void draw(const std::string& id, int x, int y, double angle = 0, int alpha = 255, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(const std::string& id, int x, int y, int destW, int destH, double angle = 0, int alpha = 255, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(const std::string& id, int x, int y, int frame_width, int frame_height,
		int& current_row, int& current_frame, int frame_number, int row_number, float speed_factor,
		double angle, int alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawText(const std::string& id, int x, int y, double angle, int alpha = 255, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawTile(const std::string& id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame);
	void drawRect(int x, int y, int w, int h, const SDL_Color color);
	void drawFillRect(int x, int y, int w, int h, const SDL_Color color);


	// animation functions
	void animateFrames(int frame_width, int frame_height, int frame_number, int row_number, float speed_factor, int& current_frame, int& current_row);
	void playAnimation(const std::string& sprite_sheet_name, Animation& animation, int x, int y, float speed_factor, double angle, int alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void playAnimation(Animation& animation, int x, int y, int destW, int destH, float speed_factor, double angle, int alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE, bool loop = true, std::function<void(CallbackType)> callback = nullptr, int callbackOrder = -1, bool center = false);
	SpriteSheet* getSpriteSheet(const std::string& name);

	// texture utility functions
	SDL_Texture* getTexture(const std::string& id);
	void setColour(const std::string& id, Uint8 red, Uint8 green, Uint8 blue);
	bool addTexture(const std::string& id, SDL_Texture* texture);
	void removeTexture(const std::string& id);
	glm::vec2 getTextureSize(const std::string& id);
	void setAlpha(const std::string& id, Uint8 new_alpha);
	void setAnimation(std::string id, const Animation& animation);
	std::unordered_map<std::string, Animation> getAnimation(const std::string& id);

	void setRenderer(SDL_Renderer* renderer);
	SDL_Renderer* getRenderer() const;


	// textureMap functions
	int getTextureMapSize() const;
	void displayTextureMap();
	void clean();


private:

	TextureManager();
	~TextureManager();

	// private utility functions
	bool m_textureExists(const std::string& id);
	bool m_spriteSheetExists(const std::string& sprite_sheet_name);
	bool m_animationExists(const std::string animationId, const std::string& id);

	// storage structures
	std::unordered_map<std::string, SDL_Texture*> m_textureMap;
	std::unordered_map<std::string, SpriteSheet*> m_spriteSheetMap;

	SDL_Renderer* m_pRenderer;
	std::unordered_map<std::string, std::unordered_map<std::string, Animation>> m_pAnimations;
};

#endif /* defined(__TEXTURE_MANAGER__) */