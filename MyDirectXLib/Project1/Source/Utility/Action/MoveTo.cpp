#include "MoveTo.h"
#include "Actor\GameObject.h"

Action::MoveTo::MoveTo(Vec3 destination, float time)
	: AbstractAction(time), m_Destination(destination)
{
}

Action::MoveTo::~MoveTo()
{
}

void Action::MoveTo::init()
{
	m_Origin = m_pUser->getPosition();
}

void Action::MoveTo::update(float time)
{
	Vec3 newPosition = Vec3::moveTowards(m_Origin, m_Destination, time);
	m_pUser->setPosition(newPosition);
}

void Action::MoveTo::onSuspend()
{
}