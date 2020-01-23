#include "CircleCollider2D.h"
#include "Physics\PhysicsCalc.h"

CircleCollider2D::CircleCollider2D(GameObject * pUser, float radius)
	:AbstractCollider2D(pUser), m_Radius(radius)
{
}

CircleCollider2D::~CircleCollider2D()
{
}

bool CircleCollider2D::contains(const Vec3 point)
{
	return point.sqrDistance(position());
}

float CircleCollider2D::getRadius()
{
	return m_Radius;
}

bool CircleCollider2D::isCollision(AbstractCollider2D * pCollider)
{
	return pCollider->isCollision(this);
}

bool CircleCollider2D::isCollision(BoxCollider2D * pCollider)
{
	return PhysicsCalc::isCollision2D(this, pCollider);
}

bool CircleCollider2D::isCollision(CircleCollider2D * pCollider)
{
	return PhysicsCalc::isCollision2D(this, pCollider);
}

void CircleCollider2D::fixPosition(AbstractCollider2D * pCollider)
{
	pCollider->fixPosition(this);
}

void CircleCollider2D::fixPosition(BoxCollider2D * pCollider)
{
	PhysicsCalc::isCollision2D(this, pCollider);
}

void CircleCollider2D::fixPosition(CircleCollider2D * pCollider)
{
	PhysicsCalc::isCollision2D(this, pCollider);
}
