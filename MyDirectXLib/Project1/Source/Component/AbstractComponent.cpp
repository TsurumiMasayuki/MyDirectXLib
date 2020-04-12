#include "AbstractComponent.h"
#include "Actor\GameObject.h"

AbstractComponent::AbstractComponent(GameObject* pUser, int updateOrder)
	:m_Enabled(true),
	m_pUser(pUser),
	m_UpdateOrder(updateOrder),
	m_FirstUpdate(true)
{
	m_pUser->addComponent(this);
}

AbstractComponent::~AbstractComponent()
{
	m_pUser->removeComponent(this);
}

GameObject * AbstractComponent::getUser()
{
	return m_pUser;
}

void AbstractComponent::setPosition(const Vec3 & position)
{
	m_pUser->setPosition(position);
}

Vec3 AbstractComponent::getPosition() const
{
	return m_pUser->getPosition();
}

void AbstractComponent::setAngles(const Vec3 & angles)
{
	m_pUser->setAngles(angles);
}

Vec3 AbstractComponent::getAngles() const
{
	return m_pUser->getAngles();
}

void AbstractComponent::setSize(const Vec3 & size)
{
	m_pUser->setSize(size);
}

Vec3 AbstractComponent::getSize() const
{
	return m_pUser->getSize();
}

void AbstractComponent::destroy()
{
	onDestroy();
}

void AbstractComponent::setActive(bool value)
{
	m_Enabled = value;
}

bool AbstractComponent::isActive()
{
	return m_Enabled && m_pUser->isActive();
}

void AbstractComponent::update()
{
	if (m_FirstUpdate)
	{
		onStart();
		m_FirstUpdate = false;
	}
	onUpdate();
}

int AbstractComponent::getUpdateOrder() const
{
	return m_UpdateOrder;
}
