#pragma once
#include "CharacterState.h"
#include "GameAI.h"
#include "Layer.h"
#include "LoaderParams.h"
#include "Node.h"
#include "PhysicsObject.h"
#include "SwordType.h"

class Character : public PhysicsObject
{
public:
	Character(const LoaderParams& loader);
	virtual ~Character() = default;

	virtual void draw();
	virtual void update();
	virtual void clean();

	void collision(DisplayObject* obj) override;
	// getter
	float getMoveSpeed() const;
	float getAttackSpeed() const;
	CharacterState getCurrentState() const;
	bool isFlip() const;
	bool isAttacking() const;
	bool isDead() const;
	bool isHit() const;
	SDL_Rect getAttackCollisionRect() const;
	GameAI* getGameAI() const;
	int getPresentHp() const;
	int getMaxHp() const;
	int getAlpha() const;
	bool getDetectionRadius() const;
	glm::vec2 getGridPosition();
	// setter
	void setMoveSpeed(float speed);
	void setAttackSpeed(float speed);
	void setCurrentState(CharacterState state);
	void setAttackReach(int reach);
	void setAttackPower(int power);
	void setAttackType(GameObjectType attackType);
	void setIsJumping(bool jumping);
	void setIsAttacking(bool attacking);
	void setIsDead(bool dead);
	void setIsHit(bool hit);
	void setGameAI(GameAI* ai);
	void setDetectionRadius(bool state);
	void takeDamage(int damage);
	void setNodeList(std::vector<std::vector<Node>> tileList);

	void jump();
	void moveToRight();
	void moveToLeft();
	void moveToUp();
	void moveToDown();
	void moveToRightUp();
	void moveToLeftUp();
	void moveToRightDown();
	void moveToLeftDown();
	void idle();
	void attack();
	virtual void hit();
	virtual void die();
	void makingAttackCollisionBox(SwordType type = SwordType::NONE);
	void setAttackRectSize(int w, int h);

	bool moveToPath();


	glm::vec2 getMiddlePosition();
	void calculateF(glm::vec2 goal);
	void findAStarPath();


private:
	bool m_isJumping;
	bool m_isAttacking;
	bool m_isDead;
	bool m_isHit;
	bool m_isFlip;

	SDL_Rect m_attackCollisionRect;
	SDL_Rect m_energyRect;

	float m_moveSpeed;
	float m_attackSpeed;
	int m_attackReach;

	CharacterState m_curState;
	GameObjectType m_attackType;

	int m_presentHp;
	int m_maxHp;
	int m_attackPower;

	GameAI* m_ai;
	int m_hitMotionNum;
	int m_alpha;
	bool m_isDetectionRadius;
	bool m_found;

protected:

	std::vector<std::vector<Node>> m_tileList;
	std::vector<Node*> m_closedTileList;
	std::vector<Node*> m_openTileList;
	std::vector<Node*> m_shortestTileList;


};


