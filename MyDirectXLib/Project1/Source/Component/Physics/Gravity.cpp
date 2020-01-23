#include "Gravity.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Actor\GameObject.h"
#include "Actor\IGameMediator.h"
#include "Device\GameTime.h"
#include "Math\Vec2.h"

const float Gravity::GRAVITY_ACC = 9.8f;

Gravity::Gravity(GameObject * pUser, float mass)
	: AbstractComponent(pUser),
	m_GravSpeed(0.0f),
	m_Mass(mass),
	m_isGround(false)
{
}

Gravity::~Gravity()
{
}

void Gravity::onStart()
{
	m_pGroundDetector = new GameObject(m_pUser->getGameMediator());
	new GroundDetector(m_pGroundDetector, this);

	auto collider = new BoxCollider2D(m_pGroundDetector);
	collider->isTrigger = true;
	collider->isMove = true;
	collider->setWidth(m_pUser->getSize().x * 0.8f);
	collider->setHeight(6);

	m_DetectorDistance = m_pUser->getSize().y * 0.5f;
}

void Gravity::onUpdate()
{
	float deltaTime = GameTime::getDeltaTime();
	m_GravSpeed += GRAVITY_ACC * m_Mass * deltaTime;

	m_pUser->setPosition(m_pUser->getPosition() + Vec3(0, -m_GravSpeed * deltaTime, 0));

	m_pGroundDetector->setPosition(m_pUser->getPosition() - Vec3(0, m_DetectorDistance, 0));
}

AbstractComponent::TypeID Gravity::getType() const
{
	return AbstractComponent::TGravity;
}

void Gravity::onDestroy()
{
	m_pGroundDetector->destroy();
}

float Gravity::getGravSpeed()
{
	return m_GravSpeed;
}

bool Gravity::isGround()
{
	return m_isGround;
}

Gravity::GroundDetector::GroundDetector(GameObject * pUser, Gravity * pListner)
	: AbstractComponent(pUser), m_pListner(pListner)
{
}

void Gravity::GroundDetector::onStart()
{
}

void Gravity::GroundDetector::onUpdate()
{
}

AbstractComponent::TypeID Gravity::GroundDetector::getType() const
{
	return AbstractComponent::TNone;
}

void Gravity::GroundDetector::onCollisionEnter(GameObject * pHit)
{
	if (pHit != m_pListner->getUser())
	{
		m_pListner->m_isGround = true;
		m_pListner->m_GravSpeed = 0.0f;
	}
}

void Gravity::GroundDetector::onCollisionStay(GameObject * pHit)
{
	if (pHit != m_pListner->getUser())
	{
		m_pListner->m_isGround = true;
		m_pListner->m_GravSpeed = 0.0f;
	}
}

void Gravity::GroundDetector::onCollisionExit(GameObject * pHit)
{
	if (pHit != m_pListner->getUser())
	{
		m_pListner->m_isGround = false;
	}
}