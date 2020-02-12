#include "WaitForSeconds.h"
#include "Utility\Timer.h"

Action::WaitForSeconds::WaitForSeconds(float waitTime)
	: AbstractAction(waitTime)
{
}

Action::WaitForSeconds::~WaitForSeconds()
{
}

void Action::WaitForSeconds::init()
{
}

void Action::WaitForSeconds::update(float time)
{
}

void Action::WaitForSeconds::onSuspend()
{
}

Action::WaitForSeconds * Action::WaitForSeconds::clone()
{
	return new WaitForSeconds(m_pTimer->getMaxTime());
}
