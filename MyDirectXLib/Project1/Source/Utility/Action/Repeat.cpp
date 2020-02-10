#include "Repeat.h"
#include <cstring>
#include "Actor\GameObject.h"

Action::Repeat::Repeat(AbstractAction* pAction, int repeatCount)
	:m_pAction(pAction), m_RepeatCount(repeatCount), m_RepeatCountOrigin(repeatCount - 1)
{
}

Action::Repeat::~Repeat()
{
	delete m_pAction;
}

void Action::Repeat::init()
{
	m_RepeatCount = m_RepeatCountOrigin;
	m_pAction->init();
}

void Action::Repeat::update()
{
	if (m_pAction->isEnd() && m_RepeatCount > 0)
	{
		m_pAction->init();
		m_RepeatCount--;
	}

	m_pAction->update();
}

void Action::Repeat::onSuspend()
{
	m_pAction->onSuspend();
}

bool Action::Repeat::isEnd()
{
	return m_RepeatCount <= 0;
}
