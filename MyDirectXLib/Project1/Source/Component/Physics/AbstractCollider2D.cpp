#include "AbstractCollider2D.h"
#include "Actor\GameObject.h"
#include "Actor\IGameMediator.h"
#include "Physics\PhysicsWorld.h"
#include "Physics\CollisionHit2D.h"
#include "BoxCollider2D.h"
#include <algorithm>
#include <Windows.h>

bool vectorContains(std::vector<CollisionHit2D*>& vector, CollisionHit2D* value)
{
	if (vector.size() == 0) return false;

	auto result = std::find(vector.begin(), vector.end(), value);
	return result != vector.end();
}

AbstractCollider2D::AbstractCollider2D(GameObject * pUser)
	: AbstractComponent(pUser),
	isTrigger(true),
	isMove(true),
	isPlayer(false),
	m_pCollHit2D(new CollisionHit2D(this)),
	layer(PhysicsLayer::None)
{
	pUser->addCollider(this);
	pUser->getGameMediator()->getPhysicsWorld()->addCollider(this);
}

AbstractCollider2D::~AbstractCollider2D()
{
	m_pUser->getGameMediator()->getPhysicsWorld()->removeCollider(this);
	m_pUser->removeCollider();

	m_pCollHit2D->onDelete();

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

void AbstractCollider2D::clearHitStates()
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

void AbstractCollider2D::checkHitStates()
{
	for (auto& currentHit : m_CurrentHits)
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

	for (auto& previousHit : m_PreviousHits)
	{
		if (!previousHit->isAccessable())
			continue;

		if (!vectorContains(m_CurrentHits, previousHit))
		{
			onCollisionExit(previousHit->getCollider());
		}
	}
}

void AbstractCollider2D::onCollision(AbstractCollider2D * pHit)
{
	m_CurrentHits.emplace_back(pHit->getCollHit2D());
	pHit->getCollHit2D()->onAddRef();
}

Vec3 AbstractCollider2D::position()
{
	return m_pUser->getPosition();
}

Vec3 AbstractCollider2D::size()
{
	return m_pUser->getSize();
}

Vec3 AbstractCollider2D::angles()
{
	return m_pUser->getAngles();
}

GameObject * AbstractCollider2D::getUser()
{
	return m_pUser;
}

void AbstractCollider2D::onCollisionEnter(AbstractCollider2D * pHit)
{
	m_pUser->onCollisionEnterCallBack(pHit->m_pUser);
}

void AbstractCollider2D::onCollisionStay(AbstractCollider2D * pHit)
{
	m_pUser->onCollisionStayCallBack(pHit->m_pUser);
}

void AbstractCollider2D::onCollisionExit(AbstractCollider2D * pHit)
{
	m_pUser->onCollisionExitCallBack(pHit->m_pUser);
}

CollisionHit2D * AbstractCollider2D::getCollHit2D()
{
	return m_pCollHit2D;
}

void AbstractCollider2D::onStart()
{
}

void AbstractCollider2D::onUpdate()
{

}

AbstractComponent::TypeID AbstractCollider2D::getType() const
{
	return AbstractComponent::TCollider;
}
