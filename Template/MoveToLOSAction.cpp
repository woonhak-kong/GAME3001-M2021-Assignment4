#include "MoveToLOSAction.h"

#include "Scene.h"
#include "Util.h"

MoveToLOSAction::MoveToLOSAction(Character* character) :
	ActionNode(character)
{
	//m_patrolPlaces.push_back({ 4,4 });
	m_patrolPlaces.push_back({ 5,30 });
	//m_patrolPlaces.push_back({ 5,42 });
	m_patrolPlaces.push_back({ 5,69 });
	//m_patrolPlaces.push_back({ 6,33 });
	//m_patrolPlaces.push_back({ 10,7 });
	m_patrolPlaces.push_back({ 13,64 });
	m_patrolPlaces.push_back({ 20,30 });
	m_patrolPlaces.push_back({ 20,67 });
	//m_patrolPlaces.push_back({ 25,42 });
	m_patrolPlaces.push_back({ 29,70 });
	//m_patrolPlaces.push_back({ 32,29 });
	m_patrolPlaces.push_back({ 33,6 });
	m_patrolPlaces.push_back({ 34,50 });
	m_patrolPlaces.push_back({ 37,72 });
	m_patrolPlaces.push_back({ 41,22 });


	m_curPatrolGoalIDX = 0;
	m_preShortestIDX = 99;
}

MoveToLOSAction::~MoveToLOSAction()
{
}

void MoveToLOSAction::Action()
{
	if (m_isActionDone)
	{
		int newPatrolGoal;
		auto target = m_pCharacter->getParent()->getPlayer();
		int shortestDistance = INT_MAX;
		int shortestIDX = 0;
		for (int i = 0; i < m_patrolPlaces.size(); i++)
		{
			int distance = Util::distance(static_cast<Character*>(target)->getGridPosition(), m_patrolPlaces[i]);
			if(shortestDistance > distance)
			{
				if (m_preShortestIDX != i)
				{
					shortestDistance = distance;
					//std::cout << shortestDistance << std::endl;
					shortestIDX = i;
				}
			}
		}

		m_preShortestIDX = shortestIDX;

		m_pCharacter->calculateF(m_patrolPlaces[shortestIDX]);
		m_pCharacter->findAStarPath();
		m_isActionDone = false;
	}
	else
	{
		if (!m_pCharacter->moveToPath())
		{
			m_isActionDone = true;
		}
	}
}
