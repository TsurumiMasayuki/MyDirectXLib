#include "MoveBy.h"
#include "Actor\GameObject.h"

Action::MoveBy::MoveBy(Vec3 moveValue, float time)
	: AbstractAction(time), m_MoveValue(moveValue)
{
}

Action::MoveBy::~MoveBy()
{
}

void Action::MoveBy::init()
{
	m_Origin = m_pUser->getPosition();
	m_Destination = m_Origin + m_MoveValue;
}

void Action::MoveBy::update(float time)
{
	Vec3 newPosition = Vec3::moveTowards(m_Origin, m_Destination, time);
	m_pUser->setPosition(newPosition);
}

void Action::MoveBy::onSuspend()
{
}
