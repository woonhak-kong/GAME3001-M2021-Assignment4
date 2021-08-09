#include "Scene.h"

#include <algorithm>
#include <iostream>

#include "DisplayObject.h"


Scene::Scene() :
	m_nextLayerIndex(0),
	m_player(nullptr)
{
}

Scene::~Scene()
{
	removeAllChildren();
}

void Scene::addChild(DisplayObject* child, uint32_t layer_index, std::optional<uint32_t> order_index)
{
	uint32_t index = 0;
	// If we passed in an order index, override the auto-increment value
	if (order_index.has_value())
	{
		index = order_index.value();
	}
		// If we did not pass in an order index, generate one for them
	else
	{
		index = m_nextLayerIndex++;
	}
	child->setLayerIndex(layer_index, index);
	child->m_pParentScene = this;
	m_displayList.push_back(child);
}

void Scene::addChildDuringUpdating(DisplayObject* child)
{
	//child->m_pParentScene = this;
	//child->setLayerIndex(0, m_nextLayerIndex++);
	m_addingListDuringUpdating.push_back(child);
}

void Scene::addChildRemoving(DisplayObject* child)
{
	child->m_pParentScene = this;
	m_removingListDuringUpdating.push_back(child);
}

void Scene::removeChild(DisplayObject* child)
{
	child->clean();
	delete child;
	m_displayList.erase(std::remove(m_displayList.begin(), m_displayList.end(), child), m_displayList.end());
}

void Scene::removeFromListExceptDeleting(DisplayObject* child)
{
	m_displayList.erase(std::remove(m_displayList.begin(), m_displayList.end(), child), m_displayList.end());
}

void Scene::removeAllChildren()
{
	for (auto& count : m_displayList)
	{
		count->clean();
		delete count;
		count = nullptr;
	}

	m_displayList.clear();

	for (auto& count : m_addingListDuringUpdating)
	{
		count->clean();
		delete count;
		count = nullptr;
	}

	m_addingListDuringUpdating.clear();

}


int Scene::numberOfChildren() const
{
	return m_displayList.size();
}

bool Scene::sortObjects(DisplayObject* left, DisplayObject* right)
{
	/*
	 * First check if they have the same enabled status, if they have the same enabled status,
	 * we first check to see if they're on the same layer, if they are then we sort by layer order index,
	 * otherwise we simply sort by layer index
	 * If they do not have the same enabled status, one is true and one is false, so if left is true, it gets
	 * sorted first, otherwise right is true and it goes first
	 * This will effectively sort by layer indices, and move disabled elements to the end of the list
	 */
	return
		(left->isEnabled() == right->isEnabled())
			? (left->m_layerIndex == right->m_layerIndex
				   ? left->m_layerOrderIndex < right->m_layerOrderIndex
				   : left->m_layerIndex < right->m_layerIndex)
			: left->isEnabled();
}

void Scene::updateDisplayList()
{
	std::sort(m_displayList.begin(), m_displayList.end(), sortObjects);
	for (auto& display_object : m_displayList)
	{
		if (display_object != nullptr)
		{
			if (!display_object->isEnabled())
				break;
			display_object->update();
		}
	}
	if (m_addingListDuringUpdating.size() > 0)
	{
		//m_displayList.insert(m_displayList.end(), m_addingListDuringUpdating.begin(), m_addingListDuringUpdating.end());
		for (auto& element : m_addingListDuringUpdating)
		{
			addChild(element, 4);
		}
		m_addingListDuringUpdating.clear();
	}
	for (auto& count : m_removingListDuringUpdating)
	{
		removeChild(count);
	}
	m_removingListDuringUpdating.clear();

}

void Scene::drawDisplayList()
{
	std::sort(m_displayList.begin(), m_displayList.end(), sortObjects);
	for (auto& display_object : m_displayList)
	{
		if (display_object != nullptr)
		{
			if (display_object->isEnabled() && display_object->isVisible())
			{
				display_object->draw();
			}
		}
	}
}

GameObject* Scene::getPlayer() const
{
	return m_player;
}

GameObject* Scene::getDoor() const
{
	std::cout << "getdoor" << std::endl;
	return m_door;
}

Level* Scene::getLevel() const
{
	return m_pLevel;
}

void Scene::setPlayer(GameObject* player)
{
	m_player = player;
}

void Scene::setDoor(GameObject* door)
{
	m_door = door;
}

void Scene::setLevel(Level* level)
{
	m_pLevel = level;
}


std::vector<DisplayObject*>& Scene::getDisplayList()
{
	return m_displayList;
}
std::vector< std::vector<Node>>& Scene::getNodeList()
{
	return m_nodeList;
}