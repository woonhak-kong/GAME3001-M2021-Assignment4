#pragma once
#ifndef __SCENE__
#define __SCENE__

#include "GameObject.h"
#include "DisplayObject.h"
#include <optional>
#include <vector>

#include "Level.h"
#include "Node.h"
#include "SceneState.h"


class Scene : public GameObject
{
public:
	friend class DisplayObject;
	Scene();
	virtual ~Scene();
	virtual void draw() = 0;
	virtual void clean() = 0;
	virtual void update() = 0;
	virtual bool onExit() = 0;
	virtual void handleEvents() = 0;
	virtual bool onEnter() = 0;
	virtual SceneState getState() = 0;

	void addChild(DisplayObject* child, uint32_t layer_index = 0, std::optional<uint32_t> order_index = std::nullopt);
	void addChildDuringUpdating(DisplayObject* child);
	void addChildRemoving(DisplayObject* child);
	void removeChild(DisplayObject* child);
	void removeFromListExceptDeleting(DisplayObject* child);

	void removeAllChildren();
	int numberOfChildren() const;

	void updateDisplayList();
	void drawDisplayList();

	GameObject* getPlayer() const;
	GameObject* getDoor() const;
	Level* getLevel() const;
	void setPlayer(GameObject* player);
	void setDoor(GameObject* door);
	void setLevel(Level* level);

	std::vector<DisplayObject*>& getDisplayList();
	std::vector< std::vector<Node>>& getNodeList();

private:
	uint32_t m_nextLayerIndex;
	std::vector<DisplayObject*> m_displayList;
	std::vector<DisplayObject*> m_addingListDuringUpdating;
	std::vector<DisplayObject*> m_removingListDuringUpdating;
	std::vector<std::vector<Node>> m_nodeList;

	GameObject* m_player;
	GameObject* m_door;
	Level* m_pLevel;

	static bool sortObjects(DisplayObject* left, DisplayObject* right);
};


#endif // !__SCENE__
