#include "GameObject.h"
#include "Actor\IGameMediator.h"
#include "Actor\GameObjectManager.h"
#include "Component\AbstractComponent.h"
#include "Component\ComponentManager.h"
#include "Component\Physics\AbstractCollider2D.h"

#include <cassert>
#include "Physics\PhysicsWorld.h"

GameObject::GameObject(IGameMediator* pGameMediator) :
	m_Position(Vec3::zero()),
	m_Angles(Vec3::zero()),
	m_Size(Vec3(1, 1, 1)),
	m_Enabled(true),
	m_DestroyFlag(false),
	m_FirstUpdate(true),
	m_pGameMediator(pGameMediator),
	m_pComponentManager(new ComponentManager(this))
{
	m_pGameMediator->getGameObjectManager()->add(this);
}

GameObject::~GameObject()
{
	m_pGameMediator->getGameObjectManager()->remove(this);
	delete m_pComponentManager;
}

void GameObject::objUpdate()
{
	if (m_FirstUpdate)
	{
		m_FirstUpdate = false;
		objStart();
	}

	m_pComponentManager->update();

	update();

	m_pComponentManager->checkCollision2D();
	m_pComponentManager->checkCollision3D();
}

void GameObject::addComponent(AbstractComponent * pComponent)
{
	m_pComponentManager->add(pComponent);
}

void GameObject::removeComponent(AbstractComponent * pComponent)
{
	m_pComponentManager->remove(pComponent);
}

bool GameObject::compareTag(std::string tag)
{
	return m_Tag == tag;
}

void GameObject::setActive(bool value)
{
	m_Enabled = value;

	if (m_Enabled)
		m_pComponentManager->onEnable();
	else
		m_pComponentManager->onDisable();
}

bool GameObject::isActive()
{
	return m_Enabled && !isDestroy();
}

void GameObject::setTag(std::string tag)
{
	m_Tag = tag;
}

std::string GameObject::getTag()
{
	return m_Tag;
}

void GameObject::objStart()
{
	start();
}

void GameObject::objOnDestroy()
{
	onDestroy();
}

void GameObject::destroy()
{
	m_DestroyFlag = true;
	onDestroy();
	m_pComponentManager->onDestroy();
}

bool GameObject::isDestroy()
{
	return m_DestroyFlag;
}

void GameObject::onCollisionEnterCallBack(GameObject* pHit)
{
	onCollisionEnter(pHit);
	m_pComponentManager->onCollisionEnter(pHit);
}

void GameObject::onCollisionStayCallBack(GameObject* pHit)
{
	onCollisionStay(pHit);
	m_pComponentManager->onCollisionStay(pHit);
}

void GameObject::onCollisionExitCallBack(GameObject* pHit)
{
	onCollisionExit(pHit);
	m_pComponentManager->onCollisionExit(pHit);
}

IGameMediator * GameObject::getGameMediator()
{
	return m_pGameMediator;
}

#pragma region Getter/Setter

void GameObject::setPosition(Vec3 position)
{
	m_Position = position;
	onPositionChanged(m_Position);
	m_pComponentManager->onPositionChanged(m_Position);
}

Vec3 GameObject::getPosition()
{
	return m_Position;
}

void GameObject::setAngleZ(float angle)
{
	m_Angles.z = angle;
	onAngleChanged(m_Angles);
	m_pComponentManager->onAngleChanged(m_Angles);
}

float GameObject::getAngleZ()
{
	return m_Angles.z;
}

void GameObject::setAngles(Vec3 angles)
{
	m_Angles = angles;
	onAngleChanged(m_Angles);
	m_pComponentManager->onAngleChanged(m_Angles);
}

Vec3 GameObject::getAngles()
{
	return m_Angles;
}

void GameObject::setSize(float size)
{
	m_Size = Vec3(size, size, size);
	onSizeChanged(m_Size);
	m_pComponentManager->onSizeChanged(m_Size);
}

void GameObject::setSize(Vec3 size)
{
	m_Size = size;
	onSizeChanged(m_Size);
	m_pComponentManager->onSizeChanged(m_Size);
}

Vec3 GameObject::getSize()
{
	return m_Size;
}

#pragma endregion