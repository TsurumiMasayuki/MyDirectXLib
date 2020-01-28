#include "PhysicsWorld.h"
#include "Component\Physics\AbstractCollider2D.h"
#include "Component\Physics\AbstractCollider3D.h"
#include "Physics\PhysicsLayer.h"

PhysicsWorld::PhysicsWorld(IGameMediator * pMediator)
	: m_pGameMediator(pMediator)
{
}

PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::update()
{
	for (auto collider2D : m_ColliderList2D)
	{
		collider2D->checkHitStates();
		collider2D->clearHitStates();
	}

	for (auto collider3D : m_ColliderList3D)
	{
		collider3D->checkHitStates();
		collider3D->clearHitStates();
	}
}

void PhysicsWorld::checkCollision2D(AbstractCollider2D * pCollider)
{
	//アクティブ状態でないなら何もしない
	if (!pCollider->isActive()) return;

	//他のコライダーと総当たり
	for (auto other : m_ColliderList2D)
	{
		//レイヤーのチェック
		if (!PhysicsLayer::isHitLayer(pCollider->layer, other->layer)) continue;

		//自身とは判定を行わない
		if (pCollider == other) continue;
		//アクティブ状態でないコライダーとは何もしない
		if (!other->isActive()) continue;

		//衝突判定
		if (!pCollider->isCollision(other)) continue;
		//接触時処理を呼び出す
		pCollider->onCollision(other);

		if (other->isPlayer) continue;
		if (!pCollider->isMove) continue;
		if (pCollider->isTrigger || other->isTrigger) continue;

		//接触に合わせて位置を変更
		pCollider->fixPosition(other);
	}
}

void PhysicsWorld::addCollider2D(AbstractCollider2D * pCollider)
{
	m_ColliderList2D.emplace_back(pCollider);
}

void PhysicsWorld::removeCollider2D(AbstractCollider2D * pCollider)
{
	//末尾に削除対象を移動してpopback;
	auto itr = std::find(m_ColliderList2D.begin(), m_ColliderList2D.end(), pCollider);
	if (itr != m_ColliderList2D.end())
	{
		std::iter_swap(itr, m_ColliderList2D.end() - 1);
		m_ColliderList2D.pop_back();
	}
}

void PhysicsWorld::checkCollision3D(AbstractCollider3D * pCollider)
{
	//アクティブ状態でないなら何もしない
	if (!pCollider->isActive()) return;

	//他のコライダーと総当たり
	for (auto other : m_ColliderList3D)
	{
		//レイヤーのチェック
		if (!PhysicsLayer::isHitLayer(pCollider->layer, other->layer)) continue;

		//自身とは判定を行わない
		if (pCollider == other) continue;
		//アクティブ状態でないコライダーとは何もしない
		if (!other->isActive()) continue;

		//衝突判定
		if (!pCollider->isCollision(other)) continue;
		//接触時処理を呼び出す
		pCollider->onCollision(other);

		if (!pCollider->isMove) continue;
		if (pCollider->isTrigger || other->isTrigger) continue;

		//接触に合わせて位置を変更
		pCollider->fixPosition(other);
	}
}

void PhysicsWorld::addCollider3D(AbstractCollider3D * pCollider)
{
	m_ColliderList3D.emplace_back(pCollider);
}

void PhysicsWorld::removeCollider3D(AbstractCollider3D * pCollider)
{
	//末尾に削除対象を移動してpopback;
	auto itr = std::find(m_ColliderList3D.begin(), m_ColliderList3D.end(), pCollider);
	if (itr != m_ColliderList3D.end())
	{
		std::iter_swap(itr, m_ColliderList3D.end() - 1);
		m_ColliderList3D.pop_back();
	}
}

bool PhysicsWorld::checkCollisionDistance(AbstractCollider2D* coll1, AbstractCollider2D* coll2)
{
	return true;
}
