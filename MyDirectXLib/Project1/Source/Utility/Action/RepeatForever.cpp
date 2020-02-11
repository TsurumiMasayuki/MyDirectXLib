#include "RepeatForever.h"
#include <cstring>
#include "Actor\GameObject.h"

Action::RepeatForever::RepeatForever(AbstractAction* pAction)
	: m_pAction(pAction)
{
}

Action::RepeatForever::~RepeatForever()
{
	delete m_pAction;
}

void Action::RepeatForever::init()
{
	m_pAction->setUser(m_pUser);
	m_pAction->baseInit();
}

void Action::RepeatForever::update(float time)
{
	if (m_pAction->isEnd())
	{
		m_pAction->baseInit();
	}

	m_pAction->baseUpdate();
}

void Action::RepeatForever::onSuspend()
{
	m_pAction->onSuspend();
}

bool Action::RepeatForever::isEnd()
{
	return false;
}
