#include "Character.h"

#include "Camera.h"
#include "CollisionManager.h"
#include "Config.h"
#include "Game.h"
#include "TextureManager.h"
#include "algorithm"
#include "AttackBox.h"
#include "Util.h"

Character::Character(const LoaderParams& loader) :
	m_isJumping(false),
	m_isAttacking(false),
	m_isDead(false),
	m_isHit(false),
	m_isFlip(false),
	m_attackCollisionRect({0, 0, 0, 0}),
	m_moveSpeed(150),
	m_attackSpeed(1),
	m_curState(CharacterState::IDLE),
	m_attackType(GameObjectType::NONE),
	m_presentHp(loader.m_maxHp),
	m_maxHp(loader.m_maxHp),
	m_attackPower(loader.m_power),
	m_ai(nullptr),
	m_hitMotionNum(0),
	m_alpha(255),
	m_isDetectionRadius(false),
	m_found(false)
{
	getRigidBody().setMass(5);
	getRigidBody().getVelocity() = glm::vec2(0.0f, 0.0f);
	getRigidBody().getAcceleration() = glm::vec2(0.0f, 0.0f);
	getRigidBody().setColliding(false);
	getTransform().getPosition() = glm::vec2(loader.m_x, loader.m_y);
	setRealCollisionRect(loader.m_realWidth, loader.m_realHeight);
	setWidth(loader.m_widthOfTexture);
	setHeight(loader.m_heightOfTexture);


}

void Character::draw()
{
	PhysicsObject::draw();
	TextureManager::Instance().drawFillRect(getTransform().getPosition().x, getTransform().getPosition().y - 5, (static_cast<float>(m_presentHp) / static_cast<float>(m_maxHp)) * getWidth(), 5, { 255, 0, 0, 255 });


}

void Character::update()
{
	PhysicsObject::update();

	/*glm::vec2 previousPosition;
	glm::vec2 newPosition;*/

	// checking direction
	if (getRigidBody().getVelocity().x > 0)
	{
		m_isFlip = false;
	}
	else if (getRigidBody().getVelocity().x < 0)
	{
		m_isFlip = true;
	}


	// setting attackColiisonRect x, y
	if (m_isFlip)
	{
		// Left Direction
		m_attackCollisionRect.x = getRealCollisionRect().x - m_attackReach + getRealCollisionRect().w / 2;
		m_attackCollisionRect.y = getRealCollisionRect().y;

	}
	else
	{
		// Right Direction
		m_attackCollisionRect.x = getRealCollisionRect().x + getRealCollisionRect().w / 2;
		m_attackCollisionRect.y = getRealCollisionRect().y;
	}



	if (!m_isDead && m_presentHp <= 0)
	{
		die();
	}

	if (m_hitMotionNum > 0)
	{
		if (m_hitMotionNum % 2 == 0)
		{
			m_alpha = 20;
		}
		else
		{
			m_alpha = 255;
		}
		m_hitMotionNum--;
	}
	else
	{
		m_alpha = 255;
		m_isHit = false;
	}


}

void Character::clean()
{
	delete m_ai;
}

void Character::collision(DisplayObject* obj)
{
}

float Character::getMoveSpeed() const
{
	return m_moveSpeed;
}

float Character::getAttackSpeed() const
{
	return m_attackSpeed;
}

void Character::setAttackSpeed(float speed)
{
	m_attackSpeed = speed;
}

CharacterState Character::getCurrentState() const
{
	return m_curState;
}

bool Character::isFlip() const
{
	return m_isFlip;
}

bool Character::isAttacking() const
{
	return m_isAttacking;
}

bool Character::isDead() const
{
	return m_isDead;
}

bool Character::isHit() const
{
	return m_isHit;
}

SDL_Rect Character::getAttackCollisionRect() const
{
	return m_attackCollisionRect;
}

GameAI* Character::getGameAI() const
{
	return m_ai;
}

int Character::getPresentHp() const
{
	return m_presentHp;
}

int Character::getMaxHp() const
{
	return m_maxHp;
}

int Character::getAlpha() const
{
	return m_alpha;
}

bool Character::getDetectionRadius() const
{
	return m_isDetectionRadius;
}

glm::vec2 Character::getGridPosition()
{
	const int col = getTransform().getPosition().x / Config::TILE_SIZE;
	const int row = getTransform().getPosition().y / Config::TILE_SIZE;
	return glm::vec2(row, col);
}

void Character::setDetectionRadius(bool state)
{
	m_isDetectionRadius = state;
}


void Character::setMoveSpeed(float speed)
{
	m_moveSpeed = speed;
}

void Character::setCurrentState(CharacterState state)
{
	m_curState = state;
}

void Character::setAttackReach(int reach)
{
	m_attackReach = reach;
}

void Character::setAttackPower(int power)
{
	m_attackPower = power;
}

void Character::setAttackType(GameObjectType attackType)
{
	m_attackType = attackType;
}

void Character::setIsJumping(bool jumping)
{
	m_isJumping = jumping;
}

void Character::setAttackRectSize(int w, int h)
{
	m_attackCollisionRect.w = w;
	if (h == 0)
	{
		m_attackCollisionRect.h = getRealCollisionRect().h;
	}
	else
	{
		m_attackCollisionRect.h = h;
	}

}

bool Character::moveToPath()
{

	if(!m_shortestTileList.empty())
	{

		int posX = m_shortestTileList.back()->m_x + Config::TILE_SIZE/2;
		int posY = m_shortestTileList.back()->m_y + Config::TILE_SIZE / 2;
		int groundCollisionX = getGroundCollision().x + getGroundCollision().w/2;
		int groundCollisionY = getGroundCollision().y + getGroundCollision().h/2;

		if(groundCollisionX > posX && groundCollisionY > posY)
		{
			moveToLeftUp();
		}
		else if (groundCollisionX > posX && groundCollisionY < posY)
		{
			moveToLeftDown();
		}
		else if (groundCollisionX < posX && groundCollisionY > posY)
		{
			moveToRightUp();
		}
		else if (groundCollisionX < posX && groundCollisionY < posY)
		{
			moveToRightDown();
		}
		else if (groundCollisionX > posX && abs(groundCollisionY - posY) < 1)
		{
			moveToLeft();
		}
		else if (groundCollisionX < posX && abs(groundCollisionY - posY) < 1)
		{
			moveToRight();
		}
		else if (groundCollisionY > posY && abs(groundCollisionX - posX) < 1)
		{
			moveToUp();
		}
		else if (groundCollisionY < posY && abs(groundCollisionX - posX) < 1)
		{
			moveToDown();
		}

		if (Util::distance({ groundCollisionX, groundCollisionY }, { posX, posY}) < 10)
		{
			m_shortestTileList.pop_back();
		}
		return true;
	}
	return false;
}

glm::vec2 Character::getMiddlePosition()
{
	glm::vec2 middlePosition(getTransform().getPosition().x + getWidth() * 0.5f, getTransform().getPosition().y + getHeight() * 0.5f);
	return middlePosition;
}

void Character::calculateF(glm::vec2 goal)
{
	int g, h, f;
	m_tileList.clear();
	m_tileList = getParent()->getNodeList();
	m_tileList[goal.x][goal.y].setStatus(NodeStatus::GOAL);
	for (int row = 0; row < m_tileList.size(); row++)
	{
		for (int col = 0; col < m_tileList[0].size(); col++)
		{
			g = abs(this->getGridPosition().x * 10 - m_tileList[row][col].m_row * 10) + abs(this->getGridPosition().y * 10 - m_tileList[row][col].m_col * 10);
			h = abs(goal.x * 10 - m_tileList[row][col].m_row * 10) + abs(goal.y * 10 - m_tileList[row][col].m_col * 10);
			m_tileList[row][col].m_g = g;
			m_tileList[row][col].m_h = h;
			m_tileList[row][col].m_f = g + h;
			//std::cout << g << ", ";
			//m_tileList[row][col].m_label.setText(std::to_string(m_tileList[row][col].m_f), {255,255,0,255});
			//m_tileList[row][col].m_label.setText(std::to_string(row) + "," + std::to_string(col), {255,255,0,255});
			//m_tileList[row][col].m_label.getTransform().getPosition().x = m_tileList[row][col].m_x + Config::TILE_SIZE / 2;
			//m_tileList[row][col].m_label.getTransform().getPosition().y = m_tileList[row][col].m_y + Config::TILE_SIZE * 0.8f;
		}
		//std::cout << std::endl;
	}

	//for (auto tile : m_tileList)
	//{
	//	g = abs(player->getGridPosition().x * 10 - tile->getGridPosition().x * 10) + abs(player->getGridPosition().y * 10 - tile->getGridPosition().y * 10);
	//	if (m_euclidean)
	//	{
	//		h = Util::distance(glm::vec2(goal->getGridPosition().x * 10, goal->getGridPosition().y * 10), glm::vec2(tile->getGridPosition().x * 10, tile->getGridPosition().y * 10));
	//	}
	//	else
	//	{
	//		h = abs(goal->getGridPosition().x * 10 - tile->getGridPosition().x * 10) + abs(goal->getGridPosition().y * 10 - tile->getGridPosition().y * 10);
	//	}


	//	tile->setG(g);
	//	tile->setH(h);
	//	tile->setF(g + h);

	//}
}

void Character::findAStarPath()
{
	Node* curTile = nullptr;
	m_found = false;
	m_closedTileList.clear();
	m_openTileList.clear();
	m_shortestTileList.clear(); // for moving
	//curTile = getTileByGrid(m_player->getGridPosition());
	//curTile->setF(0);
	m_openTileList.push_back(&m_tileList[(this->getGroundCollision().y) / Config::TILE_SIZE][(this->getGroundCollision().x + 16) / Config::TILE_SIZE]);
	m_openTileList[0]->setStatus(NodeStatus::OPEN);

	int a = 0;
	while (!m_openTileList.empty())
	{
		int cost = std::numeric_limits<int>::max();
		int theLeastIdx = 0;
		for (int i = 0; i < m_openTileList.size(); i++)
		{
			// find the least F cost tile
			if (cost > m_openTileList[i]->m_f)
			{
				cost = m_openTileList[i]->m_f;
				theLeastIdx = i;
			}

		}
		curTile = m_openTileList[theLeastIdx];
		m_closedTileList.push_back(curTile);
		m_openTileList.erase(m_openTileList.begin() + theLeastIdx);

		curTile->setStatus(NodeStatus::CLOSED);

		// push back Neighbour of the least tile
		//auto map = curTile->getNeighbourMap();
		std::vector<Node*> neighbour;
		neighbour.push_back(&(m_tileList[curTile->m_row-1][curTile->m_col]));
		neighbour.push_back(&(m_tileList[curTile->m_row][curTile->m_col-1]));
		neighbour.push_back(&(m_tileList[curTile->m_row+1][curTile->m_col]));
		neighbour.push_back(&(m_tileList[curTile->m_row][curTile->m_col+1]));

		for (auto& node : neighbour)
		{

		/*}
		for (int i = 0; i < static_cast<int>(NeighbourDirection::NUM_OF_DIRECTION); i++)
		{*/

			Node* tmp = node;//map[static_cast<NeighbourDirection>(i)];

			if (tmp != nullptr && tmp->getStatus() != NodeStatus::CLOSED && !tmp->m_isCollidable &&
				!m_tileList[node->m_row - 1][node->m_col].m_isCollidable &&
				!m_tileList[node->m_row ][node->m_col - 1].m_isCollidable&&
				!m_tileList[node->m_row + 1][node->m_col].m_isCollidable&&
				!m_tileList[node->m_row ][node->m_col + 1].m_isCollidable
				)//   tmp->getTileStatus() != NodeStatus::IMPASSABLE)
			{
				bool exist = false;
				// if there is no tile in openList;
				for (auto tile : m_openTileList)
				{
					if (tile == tmp)
					{
						exist = true;
						break;

					}
				}
				if (!exist)
				{
					if (tmp->getStatus() == NodeStatus::GOAL)
					{
						// done
						m_closedTileList.push_back(tmp);
						tmp->setParrentTile(curTile);
						m_openTileList.clear();
						m_found = true;
						break;
					}
					m_openTileList.push_back(tmp);
					tmp->setStatus(NodeStatus::OPEN);
					tmp->setParrentTile(curTile);
				}
			}
		}
	}

	if (m_found)
	{

		Node* tmp = m_closedTileList.back();
		while (tmp->getParrentTile() != nullptr)
		{
			//m_shortestTileList.insert(m_shortestTileList.begin(), tmp);
			m_shortestTileList.push_back(tmp);
			tmp->setStatus(NodeStatus::PATH);
			tmp = tmp->getParrentTile();

		}
		//m_player->setShortestTile(m_shortestTileList);
		for (auto tile : m_shortestTileList)
		{
			//std::cout << "(" << tile->m_row << ", " << tile->m_col << ")" << std::endl;
			tile->m_label.setText("**", { 0,255,0,255 });
		}
		//std::cout << std::endl;
	}
}

void Character::setIsAttacking(bool attacking)
{
	m_isAttacking = attacking;
}

void Character::setIsDead(bool dead)
{
	m_isDead = dead;
}

void Character::setIsHit(bool hit)
{
	m_isHit = hit;
}

void Character::setGameAI(GameAI* ai)
{
	m_ai = ai;
}

void Character::takeDamage(int damage)
{
	if (!m_isDead)
	{
		m_presentHp = m_presentHp - damage;
		if (m_presentHp < 0)
		{
			m_presentHp = 0;
		}
		hit();
	}
}

void Character::setNodeList(std::vector<std::vector<Node>> tileList)
{
	m_tileList = tileList;
}


void Character::jump()
{
	calculateF({ 5, 30 });
	findAStarPath();
	/*if (!m_isDead)
	{
		if (!m_isJumping && !m_isAttacking && !m_isHit)
		{
			getRigidBody().getVelocity().y = -(getRigidBody().getMass() * getFallingRate());
			m_isJumping = true;
			m_curState = CharacterState::JUMP;
		}
	}*/
}

void Character::moveToRight()
{

	if (!m_isDead)
	{
		if (m_isJumping)
		{
			getRigidBody().getVelocity().x = m_moveSpeed;
			getRigidBody().getVelocity().y = 0;
		}
		else
		{
			if (!m_isAttacking && !m_isHit)
			{
				getRigidBody().getVelocity().x = m_moveSpeed;
				getRigidBody().getVelocity().y = 0;
				m_curState = CharacterState::RUN;
			}
		}
	}
}

void Character::moveToLeft()
{
	if (!m_isDead)
	{
		if (m_isJumping)
		{
			getRigidBody().getVelocity().x = -m_moveSpeed;
			getRigidBody().getVelocity().y = 0;
		}
		else
		{
			if (!m_isAttacking && !m_isHit)
			{
				getRigidBody().getVelocity().x = -m_moveSpeed;
				getRigidBody().getVelocity().y = 0;
				m_curState = CharacterState::RUN;
			}
		}
	}
}

void Character::moveToUp()
{

	if (!m_isDead)
	{
		if (m_isJumping)
		{
			getRigidBody().getVelocity().y = -m_moveSpeed;
			getRigidBody().getVelocity().x = 0;
		}
		else
		{
			if (!m_isAttacking && !m_isHit)
			{
				getRigidBody().getVelocity().y = -m_moveSpeed;
				getRigidBody().getVelocity().x = 0;
				m_curState = CharacterState::RUN;
			}
		}
	}
}

void Character::moveToDown()
{
	if (!m_isDead)
	{
		if (m_isJumping)
		{
			getRigidBody().getVelocity().y = +m_moveSpeed;
			getRigidBody().getVelocity().x = 0;
		}
		else
		{
			if (!m_isAttacking && !m_isHit)
			{
				getRigidBody().getVelocity().y = +m_moveSpeed;
				getRigidBody().getVelocity().x = 0;
				m_curState = CharacterState::RUN;
			}
		}
	}
}

void Character::moveToRightUp()
{
	if (!m_isDead)
	{
		if (!m_isAttacking && !m_isHit)
		{
			getRigidBody().getVelocity().x = +m_moveSpeed;
			getRigidBody().getVelocity().y = -m_moveSpeed;

			m_curState = CharacterState::RUN;
		}
	}
}

void Character::moveToLeftUp()
{
	if (!m_isDead)
	{
		if (!m_isAttacking && !m_isHit)
		{

			getRigidBody().getVelocity().x = -m_moveSpeed;
			getRigidBody().getVelocity().y = -m_moveSpeed;

			m_curState = CharacterState::RUN;
		}
	}
}

void Character::moveToRightDown()
{
	if (!m_isDead)
	{
		if (!m_isAttacking && !m_isHit)
		{
			getRigidBody().getVelocity().x = +m_moveSpeed;
			getRigidBody().getVelocity().y = +m_moveSpeed;

			m_curState = CharacterState::RUN;
		}
	}
}

void Character::moveToLeftDown()
{
	if (!m_isDead)
	{
		if (!m_isAttacking && !m_isHit)
		{
			getRigidBody().getVelocity().x = -m_moveSpeed;
			getRigidBody().getVelocity().y = +m_moveSpeed;

			m_curState = CharacterState::RUN;
		}
	}
}

void Character::idle()
{
	if (!m_isDead)
	{
		getRigidBody().getVelocity().x = 0;
		getRigidBody().getVelocity().y = 0;
		if (!m_isJumping && !m_isAttacking && !m_isHit)
		{
			m_curState = CharacterState::IDLE;
		}
	}
}

void Character::attack()
{
	if (!m_isDead)
	{
		if (!m_isAttacking && !m_isHit)
		{
			m_curState = CharacterState::ATTACK;
			m_isAttacking = true;
			if (!m_isJumping)
			{
				getRigidBody().getVelocity().x = 0;
			}
		}
	}
}

void Character::hit()
{
	if (!m_isDead)
	{
		//m_curState = CharacterState::HIT;
		m_isHit = true;
		m_isAttacking = false;
		m_hitMotionNum = 20;
		getRigidBody().getVelocity().x = 0;
	}
}

void Character::die()
{
	m_curState = CharacterState::DEAD;
	m_isDead = true;
	//getParent()->addChildRemoving(this);
}

void Character::makingAttackCollisionBox(SwordType type /* = SwordType::NONE */)
{
	getParent()->addChildDuringUpdating(new AttackBox(m_attackCollisionRect, glm::vec2(m_isFlip ? getAttackSpeed() * -10 : getAttackSpeed() * 10, 0), m_attackReach, m_attackType, m_attackPower, m_isFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, type));
}
