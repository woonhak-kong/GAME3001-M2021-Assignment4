#include "ScoreManager.h"

void ScoreManager::addScore(int point)
{
	m_score += point;
}

int ScoreManager::getScore()
{
	return m_score;
}

void ScoreManager::resetScore()
{
	m_score = 0;
}
