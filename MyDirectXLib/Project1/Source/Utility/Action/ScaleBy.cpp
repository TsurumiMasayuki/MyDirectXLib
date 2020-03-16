#include "ScaleBy.h"
#include "Actor\GameObject.h"
#include "Utility\Timer.h"

Action::ScaleBy::ScaleBy(Vec3 scaleValue, float time)
	: AbstractAction(time), m_DestSize(scaleValue)
{
}

Action::ScaleBy::~ScaleBy()
{
}

void Action::ScaleBy::init()
{
	m_Origin = m_pUser->getSize();
	m_DestSize = m_Origin + m_DestSize;
}

void Action::ScaleBy::update(float time)
{
	Vec3 newSize = Vec3::moveTowards(m_Origin, m_DestSize, time);
	m_pUser->setSize(newSize);
}

void Action::ScaleBy::onSuspend()
{
}

Action::AbstractAction * Action::ScaleBy::clone()
{
	return new ScaleBy(m_DestSize, m_pTimer->getMaxTime());
}
