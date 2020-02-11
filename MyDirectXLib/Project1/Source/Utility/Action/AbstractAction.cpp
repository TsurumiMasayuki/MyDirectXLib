#include "AbstractAction.h"
#include "Utility\Timer.h"

Action::AbstractAction::AbstractAction(float time)
	: m_pUser(nullptr),
	m_pTimer(new Timer(time))
{
}

Action::AbstractAction::~AbstractAction()
{
	delete m_pTimer;
}

void Action::AbstractAction::baseInit()
{
	m_pTimer->reset();
	init();
}

void Action::AbstractAction::baseUpdate()
{
	m_pTimer->update();
	update(m_pTimer->getRatioClamped());
}

float Action::AbstractAction::getActionTime()
{
	return m_pTimer->getMaxTime();
}

bool Action::AbstractAction::isEnd()
{
	return m_pTimer->isTime();
}
