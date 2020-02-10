#include "RepeatTime.h"

Action::RepeatTime::RepeatTime(AbstractAction * pAction, float repeatTime)
	: m_pAction(pAction), m_Timer(repeatTime)
{
}

Action::RepeatTime::~RepeatTime()
{
	delete m_pAction;
}

void Action::RepeatTime::init()
{
	m_Timer.reset();
	m_pAction->init();
}

void Action::RepeatTime::update()
{
	m_Timer.update();

	if (m_pAction->isEnd() && !m_Timer.isTime())
	{
		m_pAction->init();
	}

	m_pAction->update();
}

void Action::RepeatTime::onSuspend()
{
	m_pAction->onSuspend();
}

bool Action::RepeatTime::isEnd()
{
	return m_Timer.isTime();
}