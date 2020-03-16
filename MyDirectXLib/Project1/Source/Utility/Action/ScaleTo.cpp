#include "ScaleTo.h"
#include "Actor\GameObject.h"
#include "Utility\Timer.h"

Action::ScaleTo::ScaleTo(Vec3 scaleValue, float time)
	: AbstractAction(time), m_DestSize(scaleValue)
{
}

Action::ScaleTo::~ScaleTo()
{
}

void Action::ScaleTo::init()
{
	m_Origin = m_pUser->getSize();
}

void Action::ScaleTo::update(float time)
{
	Vec3 newSize = Vec3::moveTowards(m_Origin, m_DestSize, time);
	m_pUser->setSize(newSize);
}

void Action::ScaleTo::onSuspend()
{
}

Action::AbstractAction * Action::ScaleTo::clone()
{
	return new ScaleTo(m_DestSize, m_pTimer->getMaxTime());
}
