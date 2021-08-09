#include "GameSceneStateMachine.h"

GameSceneStateMachine::GameSceneStateMachine() :
	m_gameStates(0),
	m_deleteState(0)
{
}

GameSceneStateMachine::~GameSceneStateMachine()
{
}

void GameSceneStateMachine::pushState(Scene* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}


void GameSceneStateMachine::changeState(Scene* pState)
{
	// if not empty
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->getState() == pState->getState())
		{
			// Do nothing.
			return;
		}
		if (m_gameStates.back()->onExit())
		{
			//delete m_gameStates.back(); // BUG!!!
			m_deleteState.push_back(m_gameStates.back());
			m_gameStates.pop_back();
		}

		m_gameStates.push_back(pState);
		m_gameStates.back()->onEnter();

	}
}

void GameSceneStateMachine::popState()
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			//delete m_gameStates.back();
			m_deleteState.push_back(m_gameStates.back());
			m_gameStates.pop_back();
		}
	}
}

void GameSceneStateMachine::update()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}
	deleteState();
}

void GameSceneStateMachine::render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->draw();
	}
}

void GameSceneStateMachine::handleEvents()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->handleEvents();
	}
}

void GameSceneStateMachine::deleteState()
{
	if (!m_deleteState.empty())
	{
		delete m_deleteState.back();
		m_deleteState.pop_back();

	}
}

void GameSceneStateMachine::clearState()
{
	for (std::vector<Scene*>::iterator iter = m_gameStates.begin(); iter != m_gameStates.end(); iter++)
	{
		(*iter)->onExit();
		m_deleteState.push_back((*iter));

	}
	m_gameStates.clear();
}
