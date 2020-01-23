#pragma once
#include "AbstractCollider2D.h"

class CircleCollider2D :
	public AbstractCollider2D
{
public:
	CircleCollider2D(GameObject* pUser, float radius);
	~CircleCollider2D();

	virtual bool isCollision(AbstractCollider2D * pCollider) override;
	virtual bool isCollision(BoxCollider2D * pCollider) override;
	virtual bool isCollision(CircleCollider2D * pCollider) override;
	virtual void fixPosition(AbstractCollider2D * pCollider) override;
	virtual void fixPosition(BoxCollider2D * pCollider) override;
	virtual void fixPosition(CircleCollider2D * pCollider) override;

	virtual bool contains(const Vec3 point) override;

	float getRadius();

private:
	float m_Radius;
};