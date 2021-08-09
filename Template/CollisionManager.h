#pragma once
#ifndef __COLLISION_MANAGER__
#define __COLLISION_MANAGER__

// core libraries
#include <iostream>

#include "GameObject.h"
//#include "ship.h"
#include <SDL_rect.h>
#include <vector>
#include <GLM/gtx/norm.hpp>

#include "Agent.h"
#include "Character.h"
#include "Node.h"
#include "TileLayer.h"
//#include "SoundManager.h"

class CollisionManager
{
public:
	/**
	 * get squared distance between p1 and p2
	 *
	 * \param p1
	 * \param p2
	 * \return squared distance.
	 */
	static int squaredDistance(glm::vec2 p1, glm::vec2 p2);

	/**
	 * checking collision between obejct1 and obejct2 by radius.
	 *
	 * \param object1
	 * \param object2
	 * \return
	 */
	static bool squaredRadiusCheck(GameObject* object1, GameObject* object2);
	/**
	 * checking collision between obejct1 and obejct2 by AABB.
	 *
	 * \param object1
	 * \param object2
	 * \return
	 */
	static bool AABBCheck(GameObject* object1, GameObject* object2);
	static bool AABBCheckByRealCollisionBox(GameObject* object1, GameObject* object2);
	static bool AABBCheck(SDL_Rect object1, GameObject* object2);



	static bool lineLineCheck(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 line2_start, glm::vec2 line2_end);

	static bool lineRectCheck(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 rect_start, float rect_width, float rect_height);
	//static bool lineRectEdgeCheck(glm::vec2 line_start, glm::vec2 rect_start, float rect_width, float rect_height);


	//static int minSquaredDistanceLineLine(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 line2_start, glm::vec2 line2_end);
	////static bool lineAABBCheck(Ship* object1, GameObject* object2);

	//static int circleAABBsquaredDistance(glm::vec2 circle_centre, int circle_radius, glm::vec2 box_start, int box_width, int box_height);
	//static bool circleAABBCheck(GameObject* object1, GameObject* object2);

	static bool pointRectCheck(glm::vec2 point, glm::vec2 rect_start, float rect_width, float rect_height);

	//static bool LOSCheck(Agent* agent, glm::vec2 end_point, const std::vector<DisplayObject*>& objects, DisplayObject* target);
	static bool LOSCheckWithNode(GameObject* self, GameObject* target);

	static bool checkCharacterTileCollision(GameObject* object1, const std::vector<TileLayer*>& collisionLayers);
	static bool checkCollideTile(GameObject* object1, const std::vector<Layer*>& collisionLayers);
	static bool checkCollideTile(const SDL_Rect& vec2, const std::vector<std::vector<Node>>& nodeList);
	static bool checkCollideTile4Missile(const SDL_Rect& vec2, const std::vector<std::vector<Node>>& nodeList);
	static bool checkCollideTile(SDL_Rect rect, const std::vector<Layer*>& collisionLayers);

	static bool checkCollideHorizontalTile(GameObject* object1, const std::vector<Layer*>& collisionLayers);
	static bool checkCollideVerticalTile(GameObject* object1, const std::vector<Layer*>& collisionLayers);

private:
	CollisionManager() = default;
	~CollisionManager() = default;
};

#endif /* defined (__COLLISION_MANAGER__) */