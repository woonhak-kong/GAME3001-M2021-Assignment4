#include "PatrolAction.h"

PatrolAction::PatrolAction(Character* character) :
	ActionNode(character)
{
	m_patrolPlaces.push_back({ 4,4 });
	m_patrolPlaces.push_back({ 10,7 });
	m_patrolPlaces.push_back({ 5,30 });
	m_patrolPlaces.push_back({ 20,30 });
	m_patrolPlaces.push_back({ 5,42 });
	m_patrolPlaces.push_back({ 6,33 });
	m_patrolPlaces.push_back({ 5,69 });
	m_patrolPlaces.push_back({ 13,64 });
	m_patrolPlaces.push_back({ 20,67 });
	m_patrolPlaces.push_back({ 29,70 });
	m_patrolPlaces.push_back({ 37,72 });
	m_patrolPlaces.push_back({ 34,50 });
	m_patrolPlaces.push_back({ 25,42 });
	m_patrolPlaces.push_back({ 32,29 });
	m_patrolPlaces.push_back({ 41,22 });
	m_patrolPlaces.push_back({ 33,6 });

	m_curPatrolGoalIDX = 0;
}

PatrolAction::~PatrolAction()
{
}

void PatrolAction::Action()
{
	if(m_isActionDone)
	{
		int newPatrolGoal;
		do
		{
			newPatrolGoal = rand() % m_patrolPlaces.size();
		} while (m_curPatrolGoalIDX == newPatrolGoal);

		m_pCharacter->calculateF(m_patrolPlaces[newPatrolGoal]);
		m_pCharacter->findAStarPath();
		m_isActionDone = false;
	}
	else
	{
		if(!m_pCharacter->moveToPath())
		{
			m_isActionDone = true;
		}
	}

}
