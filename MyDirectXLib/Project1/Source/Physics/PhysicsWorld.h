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

	//総当たりで判定
	void checkCollision2D(AbstractCollider2D* pCollider);
	//コライダーの登録
	void addCollider2D(AbstractCollider2D* pCollider);
	//コライダーを登録解除
	void removeCollider2D(AbstractCollider2D* pCollider);

	//総当たりで判定
	void checkCollision3D(AbstractCollider3D* pCollider);
	//コライダーの登録
	void addCollider3D(AbstractCollider3D* pCollider);
	//コライダーを登録解除
	void removeCollider3D(AbstractCollider3D* pCollider);

private:
	bool checkCollisionDistance(AbstractCollider2D* coll1, AbstractCollider2D* coll2);

private:
	//コライダー管理用vector
	std::vector<AbstractCollider2D*> m_ColliderList2D;
	std::vector<AbstractCollider3D*> m_ColliderList3D;

	IGameMediator* m_pGameMediator;
};