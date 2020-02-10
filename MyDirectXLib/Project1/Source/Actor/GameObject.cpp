#include "GameObject.h"
#include "Actor\IGameMediator.h"
#include "Actor\GameObjectManager.h"
#include "Component\AbstractComponent.h"
#include "Component\Transform.h"
#include "Component\ComponentManager.h"

#include <cassert>
#include "Physics\PhysicsWorld.h"

GameObject::GameObject(IGameMediator* pGameMediator) :
	m_Enabled(true),
	m_DestroyFlag(false),
	m_FirstUpdate(true),
	m_pGameMediator(pGameMediator),
	m_pComponentManager(new ComponentManager(this))
{
	m_pGameMediator->getGameObjectManager()->add(this);
	m_pTransform = new Transform(this);
}

GameObject::~GameObject()
{
	//親オブジェクトが設定されているなら自身を子オブジェクトから登録解除する
	if (m_pParent != nullptr)
		m_pParent->removeChild(*this);

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

void GameObject::setPosition(Vec3 position)
{
	m_pTransform->setPosition(position);
}

Vec3 GameObject::getPosition()
{
	return m_pTransform->getPosition();
}

void GameObject::setAngles(Vec3 angles)
{
	m_pTransform->setAngles(angles);
}

Vec3 GameObject::getAngles()
{
	return m_pTransform->getAngles();
}

void GameObject::setSize(Vec3 size)
{
	m_pTransform->setSize(size);
}

Vec3 GameObject::getSize()
{
	return m_pTransform->getSize();
}

void GameObject::setParent(GameObject* parent)
{
#if _DEBUG
	//自身が設定されたらエラー
	assert(parent != this);
#endif

	//親オブジェクトが設定されているなら自身を子オブジェクトから登録解除する
	if (m_pParent != nullptr)
		m_pParent->removeChild(*this);

	m_pParent = parent;
}

GameObject * GameObject::getParent()
{
	return m_pParent;
}

void GameObject::addChild(GameObject & child)
{
#if _DEBUG
	//自身が設定されたらエラー
	assert(&child != this);
#endif

	child.m_pParent = this;
	m_Children.emplace_back(&child);
}

void GameObject::removeChild(GameObject & child)
{
	//末尾に削除対象を移動してpopback
	auto itr = std::find(m_Children.begin(), m_Children.end(), &child);
	if (itr != m_Children.end())
	{
		std::iter_swap(itr, m_Children.end() - 1);
		m_Children.pop_back();
	}
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

	for (auto child : m_Children)
	{
		child->setActive(m_Enabled);
	}
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
	for (auto child : m_Children)
	{
		child->destroy();
	}

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