#pragma once
#ifndef __SCORE_MANAGER__
#define __SCORE_MANAGER__
class ScoreManager
{

public:

	static void addScore(int point);
	static int getScore();
	static void resetScore();

private:

	inline static int m_score;

};

#endif // __SCORE_MANAGER__