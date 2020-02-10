#include "MoveTo.h"
#include "Actor\GameObject.h"

Action::MoveTo::MoveTo(GameObject * pUser, Vec3 destination, float time)
	: m_Destination(destination), m_MoveTimer(time)
{
}

Action::MoveTo::~MoveTo()
{
}

void Action::MoveTo::init()
{
	m_Origin = m_pUser->getPosition();
	m_MoveTimer.reset();
}

void Action::MoveTo::update()
{
	m_MoveTimer.update();
	Vec3 newPosition = Vec3::moveTowards(m_Origin, m_Destination, m_MoveTimer.getRatioClamped());
	m_pUser->setPosition(newPosition);
}

void Action::MoveTo::onSuspend()
{
}

bool Action::MoveTo::isEnd()
{
	return m_MoveTimer.isTime();
}
