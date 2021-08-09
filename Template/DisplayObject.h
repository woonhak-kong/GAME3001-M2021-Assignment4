#pragma once
#ifndef __DISPLAY_OBJECT__
#define __DISPLAY_OBJECT__

#include "GameObject.h"

class Scene;

class DisplayObject : public GameObject
{
public:
	DisplayObject();
	virtual ~DisplayObject() = default;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	virtual void collision(DisplayObject* obj);

	Scene* getParent() const;
	void setParent(Scene* parent);

	/*
	 * Gets the index of the layer, layers are groups of objects that share a layer order index.
	 * Higher numbers draw on top of lower numbers
	 */
	uint32_t getLayerIndex() const;
	/*
	 * Gets the order of the display element within it's layer, higher numbers draw on top of lower numbers
	 */
	uint32_t getLayerOrderIndex() const;
	/*
	 * Sets the layer index and order index for this display object, higher numbers draw on top of lower numbers
	 * @param new_index The new layer index
	 * @param new_order The order within the layer, default is zero
	 */
	void setLayerIndex(uint32_t new_index, uint32_t new_order = 0);


private:
	friend class Scene;
	uint32_t m_layerIndex;
	uint32_t m_layerOrderIndex;
	Scene* m_pParentScene;
};
#endif // !__DISPLAY_OBJECT__
