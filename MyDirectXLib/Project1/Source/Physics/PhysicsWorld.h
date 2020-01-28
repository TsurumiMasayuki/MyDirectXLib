#pragma once
#include <vector>

class AbstractCollider2D;
class AbstractCollider3D;
class IGameMediator;

class PhysicsWorld
{
public:
	PhysicsWorld(IGameMediator* pMediator);
	~PhysicsWorld();

	void update();

	void checkCollision2D(AbstractCollider2D* pCollider);
	void addCollider2D(AbstractCollider2D* pCollider);
	void removeCollider2D(AbstractCollider2D* pCollider);

	void checkCollision3D(AbstractCollider3D* pCollider);
	void addCollider3D(AbstractCollider3D* pCollider);
	void removeCollider3D(AbstractCollider3D* pCollider);

private:
	bool checkCollisionDistance(AbstractCollider2D* coll1, AbstractCollider2D* coll2);

private:
	std::vector<AbstractCollider2D*> m_ColliderList2D;
	std::vector<AbstractCollider3D*> m_ColliderList3D;

	IGameMediator* m_pGameMediator;
};