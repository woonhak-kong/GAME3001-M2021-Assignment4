#include "CollisionManager.h"
//#include "Util.h"
#include <algorithm>

#include "Config.h"
#include "Game.h"
#include "GameObjectType.h"
#include "SoundManager.h"
#include "Util.h"


int CollisionManager::squaredDistance(const glm::vec2 p1, const glm::vec2 p2)
{
	const int diffOfXs = p2.x - p1.x;
	const int diffOfYs = p2.y - p1.y;
	const auto result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}

bool CollisionManager::squaredRadiusCheck(GameObject* object1, GameObject* object2)
{
	glm::vec2 P1 = object1->getTransform().getPosition();
	glm::vec2 P2 = object2->getTransform().getPosition();
	const int halfHeights = (object1->getHeight() + object2->getHeight()) * 0.5f;

	//if (glm::distance(P1, P2) < halfHeights) {

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights))
	{
		object1->getRigidBody().setColliding(true);
		object2->getRigidBody().setColliding(true);

		//switch (object2->getType()) {
		//	case TARGET:
		//		std::cout << "Collision with Target!" << std::endl;
		//		SoundManager::Instance().playSound("yay", 0);


		//		break;
		//	default:

		//		break;
		//}


		return true;
	}
	else
	{

		object1->getRigidBody().setColliding(false);
		object2->getRigidBody().setColliding(false);
		return false;
	}
}

bool CollisionManager::AABBCheck(GameObject* object1, GameObject* object2)
{
	// prepare relevant variables
	const auto p1 = object1->getTransform().getPosition();
	const auto p2 = object2->getTransform().getPosition();
	const float p1Width = object1->getWidth();
	const float p1Height = object1->getHeight();
	const float p2Width = object2->getWidth();
	const float p2Height = object2->getHeight();

	if (
		p1.x < p2.x + p2Width &&
		p1.x + p1Width > p2.x &&
		p1.y < p2.y + p2Height &&
		p1.y + p1Height > p2.y
		)
	{
		object1->getRigidBody().setColliding(true);
		object2->getRigidBody().setColliding(true);

		//switch (object2->getType())
		//{
		//case TARGET:
		//	std::cout << "Collision with Target!" << std::endl;
		//	SoundManager::Instance().playSound("yay", 0);
		//	break;
		//case OBSTACLE:
		//	std::cout << "Collision with Obstacle!" << std::endl;
		//	SoundManager::Instance().playSound("yay", 0);
		//	break;
		//default:

		//	break;
		//}

		return true;
	}
	else
	{
		object1->getRigidBody().setColliding(false);
		object2->getRigidBody().setColliding(false);
		return false;
	}
}

bool CollisionManager::AABBCheckByRealCollisionBox(GameObject* object1, GameObject* object2)
{
	// prepare relevant variables
	const auto p1 = glm::vec2(object1->getRealCollisionRect().x, object1->getRealCollisionRect().y);
	const auto p2 = glm::vec2(object2->getRealCollisionRect().x, object2->getRealCollisionRect().y);
	const float p1Width = object1->getRealCollisionRect().w;
	const float p1Height = object1->getRealCollisionRect().h;
	const float p2Width = object2->getRealCollisionRect().w;
	const float p2Height = object2->getRealCollisionRect().h;

	if (
		p1.x < p2.x + p2Width &&
		p1.x + p1Width > p2.x &&
		p1.y < p2.y + p2Height &&
		p1.y + p1Height > p2.y
		)
	{
		object1->getRigidBody().setColliding(true);
		object2->getRigidBody().setColliding(true);

		//switch (object2->getType())
		//{
		//case TARGET:
		//	std::cout << "Collision with Target!" << std::endl;
		//	SoundManager::Instance().playSound("yay", 0);
		//	break;
		//case OBSTACLE:
		//	std::cout << "Collision with Obstacle!" << std::endl;
		//	SoundManager::Instance().playSound("yay", 0);
		//	break;
		//default:

		//	break;
		//}

		return true;
	}
	else
	{
		object1->getRigidBody().setColliding(false);
		object2->getRigidBody().setColliding(false);
		return false;
	}
}

bool CollisionManager::AABBCheck(SDL_Rect object1, GameObject* object2)
{
	// prepare relevant variables
	const glm::vec2 p1 = glm::vec2(object1.x, object1.y);
	const auto p2 = glm::vec2(object2->getRealCollisionRect().x, object2->getRealCollisionRect().y);
	const float p1Width = object1.w;
	const float p1Height = object1.h;
	const float p2Width = object2->getRealCollisionRect().w;
	const float p2Height = object2->getRealCollisionRect().h;

	if (
		p1.x < p2.x + p2Width &&
		p1.x + p1Width > p2.x &&
		p1.y < p2.y + p2Height &&
		p1.y + p1Height > p2.y
		)
	{
		object2->getRigidBody().setColliding(true);
		return true;
	}
	else
	{
		object2->getRigidBody().setColliding(false);
		return false;
	}
}


bool CollisionManager::lineLineCheck(const glm::vec2 line1_start, const glm::vec2 line1_end,
                                     const glm::vec2 line2_start, const glm::vec2 line2_end)
{
	const auto x1 = line1_start.x;
	const auto x2 = line1_end.x;
	const auto x3 = line2_start.x;
	const auto x4 = line2_end.x;
	const auto y1 = line1_start.y;
	const auto y2 = line1_end.y;
	const auto y3 = line2_start.y;
	const auto y4 = line2_end.y;

	// calculate the distance to intersection point
	const auto uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	const auto uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		return true;
	}

	return false;
}

bool CollisionManager::lineRectCheck(const glm::vec2 line_start, const glm::vec2 line_end, const glm::vec2 rect_start,
                                     const float rect_width, const float rect_height)
{
	const auto x1 = line_start.x;
	const auto x2 = line_end.x;
	const auto y1 = line_start.y;
	const auto y2 = line_end.y;
	const auto rx = rect_start.x;
	const auto ry = rect_start.y;
	const auto rw = rect_width;
	const auto rh = rect_height;

	// check if the line has hit any of the rectangle's sides
	// uses the Line/Line function below
	const auto left = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx, ry + rh));
	const auto right = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx + rw, ry),
	                                 glm::vec2(rx + rw, ry + rh));
	const auto top = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx + rw, ry));
	const auto bottom = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry + rh),
	                                  glm::vec2(rx + rw, ry + rh));

	// if ANY of the above are true, the line
	// has hit the rectangle
	if (left || right || top || bottom)
	{
		return true;
	}

	return false;
}

//bool CollisionManager::lineRectEdgeCheck(const glm::vec2 line_start, const glm::vec2 rect_start, const float rect_width,
//                                         const float rect_height)
//{
//	bool state = false;
//
//	const auto x1 = line_start.x;
//	const auto y1 = line_start.y;
//
//	const auto rx = rect_start.x;
//	const auto ry = rect_start.y;
//	const auto rw = rect_width;
//	const auto rh = rect_height;
//
//	// configure the left edge
//	const auto leftEdgeStart = glm::vec2(rx, ry);
//	const auto leftEdgeEnd = glm::vec2(rx, ry + rh);
//	const auto leftEdgeMidPoint = Util::lerp(leftEdgeStart, leftEdgeEnd, 0.5f);
//
//	// configure the right edge
//	const auto rightEdgeStart = glm::vec2(rx + rw, ry);
//	const auto rightEdgeEnd = glm::vec2(rx + rw, ry + rh);
//	const auto rightEdgeMidPoint = Util::lerp(rightEdgeStart, rightEdgeEnd, 0.5f);
//
//	// configure the top edge
//	const auto topEdgeStart = glm::vec2(rx, ry);
//	const auto topEdgeEnd = glm::vec2(rx + rw, ry);
//	const auto topEdgeMidPoint = Util::lerp(topEdgeStart, topEdgeEnd, 0.5f);
//
//	// configure the bottom edge
//	const auto bottomEdgeStart = glm::vec2(rx, ry + rh);
//	const auto bottomEdgeEnd = glm::vec2(rx + rw, ry + rh);
//	const auto bottomEdgeMidPoint = Util::lerp(bottomEdgeStart, bottomEdgeEnd, 0.5f);
//
//	// line / line comparisons
//	const auto left = lineLineCheck(glm::vec2(x1, y1), leftEdgeMidPoint, leftEdgeStart, leftEdgeEnd);
//	const auto right = lineLineCheck(glm::vec2(x1, y1), rightEdgeMidPoint, rightEdgeStart, rightEdgeEnd);
//	const auto top = lineLineCheck(glm::vec2(x1, y1), topEdgeMidPoint, topEdgeStart, topEdgeEnd);
//	const auto bottom = lineLineCheck(glm::vec2(x1, y1), bottomEdgeMidPoint, bottomEdgeStart, bottomEdgeEnd);
//
//	// return true if any line collides with the edge
//	if (left || right || top || bottom)
//	{
//		state = true;
//	}
//
//
//	return state;
//}
//
//int CollisionManager::minSquaredDistanceLineLine(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 line2_start,
//                                                 glm::vec2 line2_end)
//{
//	auto u = line1_end - line1_start;
//	auto v = line2_end - line2_start;
//	auto w = line1_start - line2_start;
//	auto a = Util::dot(u, u); // always >= 0
//	auto b = Util::dot(u, v);
//	auto c = Util::dot(v, v); // always >= 0
//	auto d = Util::dot(u, w);
//	auto e = Util::dot(v, w);
//	auto D = a * c - b * b; // always >= 0
//	float sc, tc;
//
//	// compute the line parameters of the two closest points
//	if (D < Util::EPSILON)
//	{
//		// the lines are almost parallel
//		sc = 0.0;
//		tc = (b > c ? d / b : e / c); // use the largest denominator
//	}
//	else
//	{
//		sc = (b * e - c * d) / D;
//		tc = (a * e - b * d) / D;
//	}
//
//	// get the difference of the two closest points
//	auto dP = w + (sc * u) - (tc * v); // =  L1(sc) - L2(tc)
//
//	auto norm = Util::dot(dP, dP);
//	return norm;
//}
//
//bool CollisionManager::lineAABBCheck(Ship* object1, GameObject* object2)
//{
//	const auto lineStart = object1->getTransform()->position;
//	const auto lineEnd = object1->getTransform()->position + object1->getCurrentDirection() * 100.0f;
//	// aabb
//	const auto boxWidth = object2->getWidth();
//	const int halfBoxWidth = boxWidth * 0.5f;
//	const auto boxHeight = object2->getHeight();
//	const int halfBoxHeight = boxHeight * 0.5f;
//	const auto boxStart = object2->getTransform()->position - glm::vec2(halfBoxWidth, halfBoxHeight);
//
//	if (lineRectCheck(lineStart, lineEnd, boxStart, boxWidth, boxHeight))
//	{
//		switch (object2->getType())
//		{
//		case TARGET:
//			std::cout << "Collision with Obstacle!" << std::endl;
//			SoundManager::Instance().playSound("yay", 0);
//
//			break;
//		default:
//
//			break;
//		}
//
//		return true;
//	}
//
//	return false;
//}
//
//int CollisionManager::circleAABBsquaredDistance(const glm::vec2 circle_centre, int circle_radius,
//                                                const glm::vec2 box_start, const int box_width, const int box_height)
//{
//	auto dx = std::max(box_start.x - circle_centre.x, 0.0f);
//	dx = std::max(dx, circle_centre.x - (box_start.x + box_width));
//	auto dy = std::max(box_start.y - circle_centre.y, 0.0f);
//	dy = std::max(dy, circle_centre.y - (box_start.y + box_height));
//
//	return (dx * dx) + (dy * dy);
//}
//
//bool CollisionManager::circleAABBCheck(GameObject* object1, GameObject* object2)
//{
//	// circle
//	const auto circleCentre = object1->getTransform()->position;
//	const int circleRadius = std::max(object1->getWidth() * 0.5f, object1->getHeight() * 0.5f);
//	// aabb
//	const auto boxWidth = object2->getWidth();
//	int halfBoxWidth = boxWidth * 0.5f;
//	const auto boxHeight = object2->getHeight();
//	int halfBoxHeight = boxHeight * 0.5f;
//
//	const auto boxStart = object2->getTransform()->position - glm::vec2(boxWidth * 0.5f, boxHeight * 0.5f);
//
//	if (circleAABBsquaredDistance(circleCentre, circleRadius, boxStart, boxWidth, boxHeight) <= (circleRadius *
//		circleRadius))
//	{
//		if (!object2->getRigidBody()->isColliding)
//		{
//			object2->getRigidBody()->isColliding = true;
//
//			const auto attackVector = object1->getTransform()->position - object2->getTransform()->position;
//			const auto normal = glm::vec2(0.0f, -1.0f);
//
//			const auto dot = Util::dot(attackVector, normal);
//			const auto angle = acos(dot / Util::magnitude(attackVector)) * Util::Rad2Deg;
//
//			switch (object2->getType())
//			{
//			case TARGET:
//				std::cout << "Collision with Planet!" << std::endl;
//				SoundManager::Instance().playSound("yay", 0);
//				break;
//			case SHIP:
//				{
//					SoundManager::Instance().playSound("thunder", 0);
//					auto velocityX = object1->getRigidBody()->velocity.x;
//					auto velocityY = object1->getRigidBody()->velocity.y;
//
//					if ((attackVector.x > 0 && attackVector.y < 0) || (attackVector.x < 0 && attackVector.y < 0))
//						// top right or top left
//					{
//						if (angle <= 45)
//						{
//							object1->getRigidBody()->velocity = glm::vec2(velocityX, -velocityY);
//						}
//						else
//						{
//							object1->getRigidBody()->velocity = glm::vec2(-velocityX, velocityY);
//						}
//					}
//
//					if ((attackVector.x > 0 && attackVector.y > 0) || (attackVector.x < 0 && attackVector.y > 0))
//						// bottom right or bottom left
//					{
//						if (angle <= 135)
//						{
//							object1->getRigidBody()->velocity = glm::vec2(-velocityX, velocityY);
//						}
//						else
//						{
//							object1->getRigidBody()->velocity = glm::vec2(velocityX, -velocityY);
//						}
//					}
//				}
//
//
//				break;
//			default:
//
//				break;
//			}
//
//			return true;
//		}
//		return false;
//	}
//	else
//	{
//		object2->getRigidBody()->isColliding = false;
//		return false;
//	}
//
//	return false;
//}

bool CollisionManager::pointRectCheck(const glm::vec2 point, const glm::vec2 rect_start, const float rect_width,
	const float rect_height)
{
	const float topLeftX = rect_start.x - rect_width * 0.5;
	const float topLeftY = rect_start.y - rect_height * 0.5;
	const auto width = rect_width;
	const auto height = rect_height;

	if (point.x > topLeftX &&
		point.x < topLeftX + width &&
		point.y > topLeftY &&
		point.y < topLeftY + height)
	{
		return true;
	}
	return false;
}

bool CollisionManager::LOSCheckWithNode(GameObject* self, GameObject* target)
{
	auto selfCharacter = dynamic_cast<Character*>(self);
	auto targetCharacter = dynamic_cast<Character*>(target);

	glm::vec2 selfPosition = selfCharacter->getCenterPosition();
	auto list = selfCharacter->getParent()->getNodeList();

	int distanceBetweenThem = Util::distance(selfCharacter->getCenterPosition(), targetCharacter->getCenterPosition());
	int modifiedNumOfCheck = distanceBetweenThem / 10; // because tile size is 16
	for (int i = 1; i <= modifiedNumOfCheck; i++)
	{
		auto tmp = (selfCharacter->getCurrentDirection() * (static_cast<float>(i) * 10));
		glm::vec2 positionOnTheLine = selfPosition + tmp;
		//std::cout << tmp.x << ", "<< tmp.y << std::endl;
		//std::cout << positionOnTheLine.x << ", " << positionOnTheLine.y << std::endl;
		if (list[(int)positionOnTheLine.y / 16][(int)positionOnTheLine.x / 16].m_isCollidable &&
			!list[(int)positionOnTheLine.y / 16][(int)positionOnTheLine.x / 16].m_isTransparent)
		{
			return true;
		}
	}
	return false;

}

bool CollisionManager::checkCharacterTileCollision(GameObject* object1, const std::vector<TileLayer*>& collisionLayers)
{
	// iterate through collision layers
	for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
	{
		TileLayer* pTileLayer = (*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();
		// get this layers position
		glm::vec2 layerPos = pTileLayer->getPosition();
		int x, y, tileColumn, tileRow, tileid = 0;
		// calculate position on tile map
		x = layerPos.x / pTileLayer->getTileSize();
		y = layerPos.y / pTileLayer->getTileSize();
		// if moving forward or upwards
		if (object1->getRigidBody().getVelocity().x >= 0 || object1->getRigidBody().getVelocity().y >= 0)
		{
			tileColumn = (object1->getTransform().getPosition().x + object1->getWidth()) / pTileLayer->getTileSize();
			tileRow = (object1->getTransform().getPosition().y + object1->getHeight()) / pTileLayer->getTileSize();
			tileid = tiles[tileRow + y][tileColumn + x];
		}
		else if (object1->getRigidBody().getVelocity().x < 0 || object1->getRigidBody().getVelocity().y < 0) // if moving backwards or downwards
		{
			tileColumn = object1->getTransform().getPosition().x / pTileLayer->getTileSize();
			tileRow = object1->getTransform().getPosition().y / pTileLayer->getTileSize();
			tileid = tiles[tileRow + y][tileColumn + x];
		}
		if (tileid != 0) // if the tile id not blank then collide
		{
			return true;
		}
	}
}

bool CollisionManager::checkCollideTile(GameObject* object1, const std::vector<Layer*>& collisionLayers)
{

	for (std::vector<Layer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
	{
		TileLayer* pTileLayer = static_cast<TileLayer*>(*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();
		glm::vec2 layerPos = pTileLayer->getPosition();
		int x, y, tileColumn, tileRow, tileid, realTileColumn, realTimeRow = 0;
		x = layerPos.x / pTileLayer->getTileSize();
		y = layerPos.y / pTileLayer->getTileSize();

		glm::vec2 startPos;
		startPos.x  = object1->getRealCollisionRect().x;
		startPos.y = object1->getRealCollisionRect().y;

		// we need to think about character's real size that shows us.
		// because sprite width and height are not real size of character. usally bigger.
		/*startPos.x += 15;
		startPos.y += 20;*/

		// todo if startPos.x is minus, it can be crash. need to fix
		/*glm::vec2 endPos(object1->getTransform().getPosition().x + (object1->getWidth() - 15),
			(object1->getTransform().getPosition().y) + object1->getHeight() - 4);*/
		glm::vec2 endPos(object1->getRealCollisionRect().x + (object1->getRealCollisionRect().w),
			(object1->getRealCollisionRect().y ) + object1->getRealCollisionRect().h);
		for (int i = startPos.x; i < endPos.x; i++)
		{
			for (int j = startPos.y; j < endPos.y; j++)
			{
				tileColumn = i / pTileLayer->getTileSize();
				tileRow = j / pTileLayer->getTileSize();
				realTileColumn = tileColumn + x;
				realTimeRow = tileRow + y;
				if (realTileColumn < 0 || realTimeRow < 0 || realTimeRow >= tiles.size() || realTileColumn >= tiles[realTimeRow].size())
				{
					return false;
				}
				tileid = tiles[realTimeRow][realTileColumn];
				if (tileid != 0)
				{
					return true;
				}
			}
		}
	}
	return false;

}

bool CollisionManager::checkCollideTile(const SDL_Rect& vec2, const std::vector<std::vector<Node>>& nodeList)
{
	int nodeSize = nodeList[0][0].m_nodeSize;
	glm::vec2 startPosition(static_cast<int>(vec2.x) / nodeSize, static_cast<int>(vec2.y) / nodeSize);
	glm::vec2 endPosition(static_cast<int>(vec2.x + vec2.w) / nodeSize, static_cast<int>(vec2.y + vec2.h) / nodeSize);

	//std::cout << startPosition.x << "," << startPosition.y << "   " << endPosition.x << "," << endPosition.y << std::endl;
	for (int col = startPosition.x; col <= endPosition.x; col++)
	{
		for (int row = startPosition.y; row <= endPosition.y; row++)
		{
			//std::cout << row << " , " << col << std::endl;
			if (nodeList[row][col].m_isCollidable)
			{
				//std::cout << "true" << std::endl;
				return true;
			}
		}
	}

	return false;
}

bool CollisionManager::checkCollideTile4Missile(const SDL_Rect& vec2, const std::vector<std::vector<Node>>& nodeList)
{
	int nodeSize = nodeList[0][0].m_nodeSize;
	glm::vec2 startPosition(static_cast<int>(vec2.x) / nodeSize, static_cast<int>(vec2.y) / nodeSize);
	glm::vec2 endPosition(static_cast<int>(vec2.x + vec2.w) / nodeSize, static_cast<int>(vec2.y + vec2.h) / nodeSize);

	//std::cout << startPosition.x << "," << startPosition.y << "   " << endPosition.x << "," << endPosition.y << std::endl;
	for (int col = startPosition.x; col <= endPosition.x; col++)
	{
		for (int row = startPosition.y; row <= endPosition.y; row++)
		{
			//std::cout << row << " , " << col << std::endl;
			if (nodeList[row][col].m_isCollidable && !nodeList[row][col].m_isTransparent)
			{
				//std::cout << "true" << std::endl;
				return true;
			}
		}
	}

	return false;
}

bool CollisionManager::checkCollideTile(SDL_Rect rect, const std::vector<Layer*>& collisionLayers)
{


	for (std::vector<Layer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
	{
		TileLayer* pTileLayer = static_cast<TileLayer*>(*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();
		glm::vec2 layerPos = pTileLayer->getPosition();
		int tileColumn, tileRow, tileid, realTileColumn, tileSize, realTimeRow = 0;
		tileSize = pTileLayer->getTileSize();
		int x = layerPos.x / tileSize;
		int y = layerPos.y / tileSize;

		glm::vec2 startPos(rect.x, rect.y);

		// we need to think about character's real size that shows us.
		// because sprite width and height are not real size of character. usally bigger.
		//startPos.x += 15;
		//startPos.y += 20;

		// todo if startPos.x is minus, it can be crash. need to fix
		glm::vec2 endPos(rect.x + rect.w, rect.y + rect.h);
		/*glm::vec2 endPos(object1->getTransform().getPosition().x + (object1->getWidth()),
			(object1->getTransform().getPosition().y) + object1->getHeight());*/
		for (int i = startPos.x; i < endPos.x; i++)
		{
			for (int j = startPos.y; j < endPos.y; j++)
			{
				tileColumn = i / tileSize;
				tileRow = j / tileSize;
				realTileColumn = tileColumn + x;
				realTimeRow = tileRow + y;
				if (realTileColumn < 0 || realTimeRow < 0 || realTimeRow >= tiles.size() || realTileColumn >= tiles[realTimeRow].size())
				{
					return false;
				}
				tileid = tiles[realTimeRow][realTileColumn];
				if (tileid != 0)
				{
					return true;
				}
			}
		}
	}
	return false;

}

bool CollisionManager::checkCollideHorizontalTile(GameObject* object1, const std::vector<Layer*>& collisionLayers)
{


	for (std::vector<Layer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
	{
		TileLayer* pTileLayer = static_cast<TileLayer*>(*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();
		glm::vec2 layerPos = pTileLayer->getPosition();
		int x, y, tileColumn, tileRow, tileid, realTileColumn, realTimeRow = 0;
		x = layerPos.x / pTileLayer->getTileSize();
		y = layerPos.y / pTileLayer->getTileSize();

		glm::vec2 startPos = object1->getTransform().getPosition();

		// we need to think about character's real size that shows us.
		// because sprite width and height are not real size of character. usally bigger.

		// todo if startPos.x is minus, it can be crash. need to fix
		glm::vec2 endPos(object1->getTransform().getPosition().x + (object1->getWidth()),
			(object1->getTransform().getPosition().y) + object1->getHeight());



		for (int i = startPos.x; i < endPos.x; i++)
		{
			for (int j = startPos.y; j < endPos.y; j++)
			{
				tileColumn = i / pTileLayer->getTileSize();
				tileRow = j / pTileLayer->getTileSize();
				realTileColumn = tileColumn + x;
				realTimeRow = tileRow + y;
				if (realTileColumn < 0 || realTimeRow < 0 || realTimeRow >= tiles.size() || realTileColumn >= tiles[realTimeRow].size())
				{
					return false;
				}
				tileid = tiles[realTimeRow][realTileColumn];
				if (tileid != 0)
				{
					return true;
				}
			}
		}
	}
	return false;

}

bool CollisionManager::checkCollideVerticalTile(GameObject* object1, const std::vector<Layer*>& collisionLayers)
{
	return true;
}

//// assumptions - the list of objects are stored so that they are facing the target and the target is loaded last
//bool CollisionManager::LOSCheck(Agent* agent, glm::vec2 end_point, const std::vector<DisplayObject*>& objects,
//                                DisplayObject* target)
//{
//	const auto start_point = agent->getTransform()->position;
//
//	for (auto object : objects)
//	{
//		auto objectOffset = glm::vec2(object->getWidth() * 0.5f, object->getHeight() * 0.5f);
//		const auto rect_start = object->getTransform()->position - objectOffset;
//		const auto width = object->getWidth();
//		const auto height = object->getHeight();
//
//		switch (object->getType())
//		{
//		case OBSTACLE:
//			if (lineRectCheck(start_point, end_point, rect_start, width, height))
//			{
//				return false;
//			}
//			break;
//		case TARGET:
//			{
//				switch (agent->getType())
//				{
//				case AGENT:
//					if (lineRectCheck(start_point, end_point, rect_start, width, height))
//					{
//						return true;
//					}
//					break;
//				case PATH_NODE:
//					if (lineRectEdgeCheck(start_point, rect_start, width, height))
//					{
//						return true;
//					}
//					break;
//				default:
//					//error
//					std::cout << "ERROR: " << agent->getType() << std::endl;
//					break;
//				}
//			}
//			break;
//		default:
//			//error
//			std::cout << "ERROR: " << object->getType() << std::endl;
//			break;
//		}
//	}
//
//	// if the line does not collide with an object that is the target then LOS is false
//	return false;
//}