#include "WaitForSeconds.h"
#include "Device\GameTime.h"

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