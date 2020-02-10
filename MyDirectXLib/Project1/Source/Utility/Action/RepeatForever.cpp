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
	m_pAction->init();
}

void Action::RepeatForever::update()
{
	if (m_pAction->isEnd())
	{
		m_pAction->init();
	}

	m_pAction->update();
}

void Action::RepeatForever::onSuspend()
{
	m_pAction->onSuspend();
}

bool Action::RepeatForever::isEnd()
{
	return false;
}
