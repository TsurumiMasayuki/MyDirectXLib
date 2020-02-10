#include "ActionManager.h"
#include "AbstractAction.h"

Action::ActionManager::ActionManager(GameObject* pUser)
	: m_pUser(pUser)
{
}

Action::ActionManager::~ActionManager()
{
	if (m_ActionQueue.size() > 0)
		m_ActionQueue.front()->onSuspend();

	while (m_ActionQueue.size() > 0)
	{
		delete m_ActionQueue.front();
		m_ActionQueue.pop();
	}
}

void Action::ActionManager::update()
{
	if (m_ActionQueue.size() <= 0)
		return;

	m_ActionQueue.front()->update();

	if (m_ActionQueue.front()->isEnd())
	{
		actionChange();
	}
}

void Action::ActionManager::enqueueAction(AbstractAction* action)
{
	m_ActionQueue.push(action);

	if (m_ActionQueue.size() == 1)
		m_ActionQueue.front()->init();
}

void Action::ActionManager::forceNext()
{
	if (m_ActionQueue.size() == 0)
		return;

	m_ActionQueue.front()->onSuspend();
	actionChange();
}

int Action::ActionManager::actionCount()
{
	return m_ActionQueue.size();
}

void Action::ActionManager::actionChange()
{
	if (m_ActionQueue.size() == 0)
		return;

	m_ActionQueue.front()->onSuspend();
	delete m_ActionQueue.front();

	m_ActionQueue.pop();

	if (m_ActionQueue.size() != 0)
	{
		m_ActionQueue.front()->baseInit(m_pUser);
		m_ActionQueue.front()->init();
	}
}
