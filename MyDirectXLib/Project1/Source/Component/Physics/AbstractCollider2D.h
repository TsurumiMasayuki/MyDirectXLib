#pragma once
#include "Math\Vec3.h"
#include "Math\Vec2.h"
#include <vector>
#include "Component\AbstractComponent.h"
#include "Physics\PhysicsLayer.h"

class GameObject;
class IGameMediator;
class CollisionHit2D;

class BoxCollider2D;
class CircleCollider2D;

class AbstractCollider2D 
	: public AbstractComponent
{
public:
	AbstractCollider2D(GameObject* pUser);
	virtual ~AbstractCollider2D();

	virtual void onStart() override;
	virtual void onUpdate() override;

	virtual void checkCollision2D() override;

	virtual bool contains(const Vec3 point) = 0;

	virtual bool isCollision(AbstractCollider2D* pCollider) = 0;
	virtual bool isCollision(BoxCollider2D* pCollider) = 0;
	virtual bool isCollision(CircleCollider2D* pCollider) = 0;

	virtual void fixPosition(AbstractCollider2D* pCollider) = 0;
	virtual void fixPosition(BoxCollider2D* pCollider) = 0;
	virtual void fixPosition(CircleCollider2D* pCollider) = 0;

	void clearHitStates();
	void checkHitStates();

	void onCollision(AbstractCollider2D* pHit);

private:
	void onCollisionEnter(AbstractCollider2D* pHit);
	void onCollisionStay(AbstractCollider2D* pHit);
	void onCollisionExit(AbstractCollider2D* pHit);

	CollisionHit2D* getCollHit2D();

public:
	bool isTrigger;
	bool isMove;
	bool isPlayer;
	PhysicsLayer::LayerEnum layer;

private:
	CollisionHit2D* m_pCollHit2D;

	std::vector<CollisionHit2D*> m_PreviousHits;
	std::vector<CollisionHit2D*> m_CurrentHits;

	std::vector<CollisionHit2D*> m_HitRefList;
};

