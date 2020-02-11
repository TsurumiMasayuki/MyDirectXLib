#include "RepeatTime.h"
#include "Utility\Timer.h"

Action::RepeatTime::RepeatTime(AbstractAction * pAction, float repeatTime)
	: AbstractAction(repeatTime), m_pAction(pAction)
{
}

Action::RepeatTime::~RepeatTime()
{
	delete m_pAction;
}

void Action::RepeatTime::init()
{
	m_pAction->setUser(m_pUser);
	m_pAction->baseInit();
}

void Action::RepeatTime::update(float time)
{
	if (m_pAction->isEnd() && !m_pTimer->isTime())
	{
		m_pAction->baseInit();
	}

	m_pAction->baseUpdate();
}

void Action::RepeatTime::onSuspend()
{
	m_pAction->onSuspend();
}