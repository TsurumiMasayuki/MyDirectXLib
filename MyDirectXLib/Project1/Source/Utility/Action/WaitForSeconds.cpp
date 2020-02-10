#include "WaitForSeconds.h"
#include "Device\GameTime.h"

Action::WaitForSeconds::WaitForSeconds(float waitTime)
	: m_Timer(waitTime)
{
}

Action::WaitForSeconds::~WaitForSeconds()
{
}

void Action::WaitForSeconds::init()
{
	m_Timer.reset();
}

void Action::WaitForSeconds::update()
{
	m_Timer.update();
}

void Action::WaitForSeconds::onSuspend()
{
}

bool Action::WaitForSeconds::isEnd()
{
	return m_Timer.isTime();
}
