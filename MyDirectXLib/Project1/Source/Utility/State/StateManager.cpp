#include "StateManager.h"

StateManager::~StateManager()
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->onStateExit();
		delete m_pCurrentState;
	}
}

void StateManager::update()
{
	m_pCurrentState->update();

	IState* pNextState = m_pCurrentState->nextState();
	if (pNextState != nullptr)
	{
		setState(pNextState);
	}
}

void StateManager::setState(IState * newState)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->onStateExit();
		delete m_pCurrentState;
	}

	m_pCurrentState = newState;
	m_pCurrentState->onStateEnter();
}

void StateManager::forceSetState(IState * newState)
{
	if (m_pCurrentState != nullptr)
		delete m_pCurrentState;

	m_pCurrentState = newState;
}
