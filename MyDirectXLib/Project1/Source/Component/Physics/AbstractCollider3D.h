#pragma once
#include "Component\AbstractComponent.h"
#include "Physics\PhysicsLayer.h"
#include <vector>

class CollisionHit3D;
class IShape3D;

class AbstractCollider3D
	: public AbstractComponent
{
public:
	AbstractCollider3D(GameObject* pUser);
	virtual ~AbstractCollider3D();

	virtual void onStart() override;
	virtual void onUpdate() override;

	virtual void checkCollision3D() override;

	void clearHitStates();
	void checkHitStates();

	bool isCollision(AbstractCollider3D* pCollider);

	void fixPosition(AbstractCollider3D* pHit);
	void onCollision(AbstractCollider3D* pHit);

protected:
	virtual IShape3D* getShape() = 0;

private:
	void onCollisionEnter(AbstractCollider3D* pHit);
	void onCollisionStay(AbstractCollider3D* pHit);
	void onCollisionExit(AbstractCollider3D* pHit);

	CollisionHit3D* getCollHit3D();

public:
	bool isTrigger;
	bool isMove;
	PhysicsLayer::LayerEnum layer;

private:
	CollisionHit3D* m_pCollHit3D;

	std::vector<CollisionHit3D*> m_PreviousHits;
	std::vector<CollisionHit3D*> m_CurrentHits;
	std::vector<CollisionHit3D*> m_HitRefList;
};