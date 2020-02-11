#include "ActionManager.h"
#include "Utility\Action\AbstractAction.h"

Action::ActionManager::ActionManager(GameObject* pUser)
	: AbstractComponent(pUser)
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

void Action::ActionManager::onStart()
{
}

void Action::ActionManager::onUpdate()
{
	if (m_ActionQueue.size() <= 0)
		return;

	m_ActionQueue.front()->baseUpdate();

	if (m_ActionQueue.front()->isEnd())
	{
		actionChange();
	}
}

void Action::ActionManager::enqueueAction(AbstractAction* action)
{
	m_ActionQueue.push(action);

	if (m_ActionQueue.size() == 1)
	{
		m_ActionQueue.front()->setUser(m_pUser);
		m_ActionQueue.front()->baseInit();
	}
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
		m_ActionQueue.front()->baseInit();
	}
}
