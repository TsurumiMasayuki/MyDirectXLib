#include "Repeat.h"
#include <cstring>
#include "Actor\GameObject.h"

Action::Repeat::Repeat(AbstractAction* pAction, int repeatCount)
	:m_pAction(pAction), m_RepeatCount(repeatCount), m_RepeatCountOrigin(repeatCount)
{
}

Action::Repeat::~Repeat()
{
	delete m_pAction;
}

void Action::Repeat::init()
{
	m_RepeatCount = m_RepeatCountOrigin;
	m_pAction->setUser(m_pUser);
	m_pAction->baseInit();
}

void Action::Repeat::update(float time)
{
	if (m_pAction->isEnd() && m_RepeatCount > 0)
	{
		m_pAction->baseInit();
		m_RepeatCount--;
	}

	m_pAction->baseUpdate();
}

void Action::Repeat::onSuspend()
{
	m_pAction->onSuspend();
}

bool Action::Repeat::isEnd()
{
	return m_RepeatCount <= 0;
}
