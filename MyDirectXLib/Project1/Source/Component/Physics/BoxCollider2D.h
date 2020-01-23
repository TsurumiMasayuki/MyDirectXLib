#pragma once
#include "AbstractCollider2D.h"

class BoxCollider2D 
	: public AbstractCollider2D
{
public:
	BoxCollider2D(GameObject* pUser);
	~BoxCollider2D();

	virtual bool isCollision(AbstractCollider2D * pCollider) override;
	virtual bool isCollision(BoxCollider2D * pCollider) override;
	virtual bool isCollision(CircleCollider2D * pCollider) override;

	virtual void fixPosition(AbstractCollider2D * pCollider) override;
	virtual void fixPosition(BoxCollider2D * pCollider) override;
	virtual void fixPosition(CircleCollider2D * pCollider) override;

	virtual bool contains(const Vec3 point) override;

	void setWidth(float width);
	void setHeight(float height);

	float getWidth();
	float getHeight();

private:
	float m_Width;
	float m_Height;

};