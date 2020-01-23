#include "ComponentManager.h"
#include "AbstractComponent.h"
#include <vector>

ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
	while (!m_Components.empty())
	{
		delete m_Components.back();
	}
}

void ComponentManager::add(AbstractComponent * pComponent)
{
	int myOrder = pComponent->getUpdateOrder();

	auto itr = m_Components.begin();
	while (itr != m_Components.end())
	{
		if (myOrder < (*itr)->getUpdateOrder())
			break;
		
		++itr;
	}

	m_Components.insert(itr, pComponent);
}

void ComponentManager::remove(AbstractComponent * pComponent)
{
	auto iter = std::find(m_Components.begin(), m_Components.end(), pComponent);
	if (iter != m_Components.end())
	{
		m_Components.erase(iter);
	}
}

void ComponentManager::update()
{
	for (auto component : m_Components)
	{
		component->update();
	}
}

void ComponentManager::onDestroy()
{
	for (auto component : m_Components)
	{
		component->onDestroy();
	}
}

void ComponentManager::onCollisionEnter(GameObject * pHit)
{
	for (auto component : m_Components)
	{
		component->onCollisionEnter(pHit);
	}
}

void ComponentManager::onCollisionStay(GameObject * pHit)
{
	for (auto component : m_Components)
	{
		component->onCollisionStay(pHit);
	}
}

void ComponentManager::onCollisionExit(GameObject * pHit)
{
	for (auto component : m_Components)
	{
		component->onCollisionExit(pHit);
	}
}

void ComponentManager::onEnable()
{
	for (auto component : m_Components)
	{
		component->onEnable();
	}
}

void ComponentManager::onDisable()
{
	for (auto component : m_Components)
	{
		component->onDisable();
	}
}