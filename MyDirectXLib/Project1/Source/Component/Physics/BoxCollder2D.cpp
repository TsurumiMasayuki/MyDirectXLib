#include "BoxCollider2D.h"
#include "Actor\GameObject.h"
#include "Physics\PhysicsCalc.h"

using namespace DirectX;

BoxCollider2D::BoxCollider2D(GameObject* pUser)
	: AbstractCollider2D(pUser)
{
	m_Width = pUser->getSize().x;
	m_Height = pUser->getSize().y;
}

BoxCollider2D::~BoxCollider2D()
{
}

bool BoxCollider2D::contains(const Vec3 point)
{
	float x = point.x;
	float y = point.y;

	Vec3 position = getUser()->getPosition();

	bool isX = position.x - m_Width / 2 < x && position.x + m_Width / 2 > x;
	bool isY = position.y - m_Height / 2 < y && position.y + m_Height / 2 > y;

	return isX && isY;
}

void BoxCollider2D::setWidth(float width)
{
	m_Width = width;
}

void BoxCollider2D::setHeight(float height)
{
	m_Height = height;
}

float BoxCollider2D::getWidth()
{
	return m_Width;
}

float BoxCollider2D::getHeight()
{
	return m_Height;
}

bool BoxCollider2D::isCollision(AbstractCollider2D * pCollider)
{
	return pCollider->isCollision(this);
}

bool BoxCollider2D::isCollision(BoxCollider2D * pCollider)
{
	return PhysicsCalc::isCollision2D(this, pCollider);
}

bool BoxCollider2D::isCollision(CircleCollider2D * pCollider)
{
	return PhysicsCalc::isCollision2D(this, pCollider);
}

void BoxCollider2D::fixPosition(AbstractCollider2D * pCollider)
{
	pCollider->fixPosition(this);
}

void BoxCollider2D::fixPosition(BoxCollider2D * pCollider)
{
	PhysicsCalc::fixPosition2D(this, pCollider);
}

void BoxCollider2D::fixPosition(CircleCollider2D * pCollider)
{
	PhysicsCalc::fixPosition2D(this, pCollider);
}