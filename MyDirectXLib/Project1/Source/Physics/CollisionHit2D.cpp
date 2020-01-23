#include "CollisionHit2D.h"

CollisionHit2D::CollisionHit2D(AbstractCollider2D * pCollider)
	: m_pCollider(pCollider),
	m_Deleted(false)
{
}

CollisionHit2D::~CollisionHit2D()
{
}

void CollisionHit2D::onDelete()
{
	m_Deleted = true;
	m_pCollider = nullptr;

	if (m_RefCount == 0)
		delete this;
}

void CollisionHit2D::onAddRef()
{
	m_RefCount++;
}

void CollisionHit2D::onRemoveRef()
{
	m_RefCount--;

	if (m_RefCount == 0 && m_Deleted)
		delete this;
}

bool CollisionHit2D::isAccessable()
{
	return !m_Deleted;
}

AbstractCollider2D * CollisionHit2D::getCollider()
{
	return m_pCollider;
}
