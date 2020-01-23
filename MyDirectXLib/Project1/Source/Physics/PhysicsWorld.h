#pragma once
#include <vector>

class AbstractCollider2D;
class IGameMediator;

class PhysicsWorld
{
public:
	PhysicsWorld(IGameMediator* pMediator);
	~PhysicsWorld();

	void update();

	void checkCollision(AbstractCollider2D* pCollider);

	void addCollider(AbstractCollider2D* pCollider);
	void removeCollider(AbstractCollider2D* pCollider);

private:
	bool checkCollisionDistance(AbstractCollider2D* coll1, AbstractCollider2D* coll2);

private:
	std::vector<AbstractCollider2D*> m_ColliderList2D;

	IGameMediator* m_pGameMediator;
};