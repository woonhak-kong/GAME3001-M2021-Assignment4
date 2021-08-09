#include "DisplayObject.h"
#include "Scene.h"

DisplayObject::DisplayObject() :
	m_layerIndex(0),
	m_layerOrderIndex(0),
	m_pParentScene(nullptr)
{
}

void DisplayObject::collision(DisplayObject* obj)
{
}

Scene* DisplayObject::getParent() const
{
	return m_pParentScene;
}

void DisplayObject::setParent(Scene* parent)
{
	m_pParentScene = parent;
}

uint32_t DisplayObject::getLayerIndex() const
{
	return m_layerIndex;
}

uint32_t DisplayObject::getLayerOrderIndex() const
{
	return m_layerOrderIndex;
}

void DisplayObject::setLayerIndex(const uint32_t new_index, const uint32_t new_order)
{
	m_layerIndex = new_index;
	m_layerOrderIndex = new_order;
}
