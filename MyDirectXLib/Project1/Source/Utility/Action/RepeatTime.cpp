#include "RepeatTime.h"
#include "Utility\Timer.h"

Action::RepeatTime::RepeatTime(AbstractAction * pTargetAction, float repeatTime)
	: AbstractAction(repeatTime), m_pTargetAction(pTargetAction)
{
}

Action::RepeatTime::~RepeatTime()
{
	delete m_pTargetAction;
}

void Action::RepeatTime::init()
{
	m_pTargetAction->setUser(m_pUser);
	m_pTargetAction->baseInit();
}

void Action::RepeatTime::update(float time)
{
	if (m_pTargetAction->isEnd() && !m_pTimer->isTime())
	{
		m_pTargetAction->baseInit();
	}

	m_pTargetAction->baseUpdate();
}

void Action::RepeatTime::onSuspend()
{
	m_pTargetAction->onSuspend();
}

Action::RepeatTime * Action::RepeatTime::clone()
{
	return new RepeatTime(m_pTargetAction->clone(), m_pTimer->getMaxTime());
}
