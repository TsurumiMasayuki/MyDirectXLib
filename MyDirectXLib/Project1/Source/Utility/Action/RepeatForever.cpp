#include "RepeatForever.h"
#include <cstring>
#include "Actor\GameObject.h"

Action::RepeatForever::RepeatForever(AbstractAction* pTargetAction)
	: m_pTargetAction(pTargetAction)
{
}

Action::RepeatForever::~RepeatForever()
{
	delete m_pTargetAction;
}

void Action::RepeatForever::init()
{
	m_pTargetAction->setUser(m_pUser);
	m_pTargetAction->baseInit();
}

void Action::RepeatForever::update(float time)
{
	if (m_pTargetAction->isEnd())
	{
		m_pTargetAction->baseInit();
	}

	m_pTargetAction->baseUpdate();
}

void Action::RepeatForever::onSuspend()
{
	m_pTargetAction->onSuspend();
}

bool Action::RepeatForever::isEnd()
{
	return false;
}

Action::RepeatForever * Action::RepeatForever::clone()
{
	return new RepeatForever(m_pTargetAction->clone());
}
