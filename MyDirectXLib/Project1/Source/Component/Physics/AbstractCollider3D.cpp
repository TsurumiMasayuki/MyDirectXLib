#include "AbstractCollider3D.h"
#include "Actor\GameObject.h"
#include "Actor\IGameMediator.h"
#include "Physics\PhysicsWorld.h"
#include "Physics\IShape3D.h"
#include "Physics\CollisionHit3D.h"

bool vectorContains(std::vector<CollisionHit3D*>& vector, CollisionHit3D* value)
{
	if (vector.size() == 0) return false;

	auto result = std::find(vector.begin(), vector.end(), value);
	return result != vector.end();
}

AbstractCollider3D::AbstractCollider3D(GameObject * pUser)
	: AbstractComponent(pUser, 300),
	isTrigger(true),
	isMove(true),
	m_pCollHit3D(new CollisionHit3D(this)),
	layer(PhysicsLayer::None)
{
	m_pUser->getGameMediator()->getPhysicsWorld()->addCollider3D(this);
}

AbstractCollider3D::~AbstractCollider3D()
{
	m_pUser->getGameMediator()->getPhysicsWorld()->removeCollider3D(this);

	m_pCollHit3D->onDelete();

	auto itr = m_CurrentHits.begin();
	while (itr != m_CurrentHits.end())
	{
		//PreviousHitsにも同じものが入っているか探す
		auto find = std::find(m_PreviousHits.begin(), m_PreviousHits.end(), (*itr));
		//入っていなかったらここで削除
		if (find == m_PreviousHits.end())
		{
			(*itr)->onRemoveRef();
		}
		++itr;
	}

	for (auto previousHit : m_PreviousHits)
	{
		previousHit->onRemoveRef();
	}
}

void AbstractCollider3D::onStart()
{
}

void AbstractCollider3D::onUpdate()
{
}

void AbstractCollider3D::checkCollision3D()
{
	m_pUser->getGameMediator()->getPhysicsWorld()->checkCollision3D(this);
}

void AbstractCollider3D::clearHitStates()
{
	for (auto previousHit : m_PreviousHits)
	{
		previousHit->onRemoveRef();
	}

	//前フレームの衝突情報をクリア
	m_PreviousHits.clear();

	//衝突情報をコピー
	std::copy(m_CurrentHits.begin(), m_CurrentHits.end(), std::back_inserter(m_PreviousHits));

	//衝突情報をクリア
	m_CurrentHits.clear();
}

void AbstractCollider3D::checkHitStates()
{
	for (auto currentHit : m_CurrentHits)
	{
		if (!currentHit->isAccessable())
			continue;

		if (!vectorContains(m_PreviousHits, currentHit))
		{
			onCollisionEnter(currentHit->getCollider());
		}
		else
		{
			onCollisionStay(currentHit->getCollider());
		}
	}

	for (auto previousHit : m_PreviousHits)
	{
		if (!previousHit->isAccessable())
			continue;

		if (!vectorContains(m_CurrentHits, previousHit))
		{
			onCollisionExit(previousHit->getCollider());
		}
	}
}

bool AbstractCollider3D::isCollision(AbstractCollider3D * pCollider)
{
	return getShape()->isIntersect(*pCollider->getShape());
}

void AbstractCollider3D::fixPosition(AbstractCollider3D * pHit)
{
	Vec3 fixPos = getShape()->getFixPosition(*pHit->getShape());
	m_pUser->setPosition(fixPos);
}

void AbstractCollider3D::onCollision(AbstractCollider3D * pHit)
{
	m_CurrentHits.emplace_back(pHit->getCollHit3D());
	pHit->getCollHit3D()->onAddRef();
}

CollisionHit3D * AbstractCollider3D::getCollHit3D()
{
	return m_pCollHit3D;
}

void AbstractCollider3D::onCollisionEnter(AbstractCollider3D * pHit)
{
	m_pUser->onCollisionEnterCallBack(pHit->m_pUser);
}

void AbstractCollider3D::onCollisionStay(AbstractCollider3D * pHit)
{
	m_pUser->onCollisionStayCallBack(pHit->m_pUser);
}

void AbstractCollider3D::onCollisionExit(AbstractCollider3D * pHit)
{
	m_pUser->onCollisionExitCallBack(pHit->m_pUser);
}