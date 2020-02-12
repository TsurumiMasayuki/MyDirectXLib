#include "Repeat.h"
#include "Actor\GameObject.h"

Action::Repeat::Repeat(AbstractAction* pTargetAction, int repeatCount)
	:m_pTargetAction(pTargetAction), m_RepeatCount(repeatCount), m_RepeatCountOrigin(repeatCount)
{
}

Action::Repeat::~Repeat()
{
	delete m_pTargetAction;
}

void Action::Repeat::init()
{
	m_RepeatCount = m_RepeatCountOrigin;
	m_pTargetAction->setUser(m_pUser);
	m_pTargetAction->baseInit();
}

void Action::Repeat::update(float time)
{
	if (m_pTargetAction->isEnd() && m_RepeatCount > 0)
	{
		m_pTargetAction->baseInit();
		m_RepeatCount--;
	}

	m_pTargetAction->baseUpdate();
}

void Action::Repeat::onSuspend()
{
	m_pTargetAction->onSuspend();
}

bool Action::Repeat::isEnd()
{
	return m_RepeatCount <= 0;
}

Action::Repeat * Action::Repeat::clone()
{
	return new Repeat(m_pTargetAction->clone(), m_RepeatCountOrigin);
}
