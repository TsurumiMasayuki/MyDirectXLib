#include "MoveBy.h"
#include "Actor\GameObject.h"

Action::MoveBy::MoveBy(Vec3 moveValue, float time)
	: m_MoveValue(moveValue), m_MoveTimer(time)
{
}

Action::MoveBy::~MoveBy()
{
}

void Action::MoveBy::init()
{
	m_Origin = m_pUser->getPosition();
	m_Destination = m_Origin + m_MoveValue;
	m_MoveTimer.reset();
}

void Action::MoveBy::update()
{
	m_MoveTimer.update();
	Vec3 newPosition = Vec3::moveTowards(m_Origin, m_Destination, m_MoveTimer.getRatioClamped());
	m_pUser->setPosition(newPosition);
}

void Action::MoveBy::onSuspend()
{
}

bool Action::MoveBy::isEnd()
{
	return m_MoveTimer.isTime();
}
