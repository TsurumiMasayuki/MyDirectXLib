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

GameObject * AbstractComponent::getUser()
{
	return m_pUser;
}

AbstractComponent::~AbstractComponent()
{
	m_pUser->removeComponent(this);
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
	return m_Enabled;
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
