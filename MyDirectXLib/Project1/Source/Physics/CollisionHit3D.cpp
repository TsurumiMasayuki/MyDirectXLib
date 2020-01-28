#include "CollisionHit3D.h"

CollisionHit3D::CollisionHit3D(AbstractCollider3D * pCollider)
	: m_pCollider(pCollider),
	m_Deleted(false)
{
}

CollisionHit3D::~CollisionHit3D()
{
}

void CollisionHit3D::onDelete()
{
	m_Deleted = true;
	m_pCollider = nullptr;

	if (m_RefCount == 0)
		delete this;
}

void CollisionHit3D::onAddRef()
{
	m_RefCount++;
}

void CollisionHit3D::onRemoveRef()
{
	m_RefCount--;

	if (m_RefCount == 0 && m_Deleted)
		delete this;
}

bool CollisionHit3D::isAccessable()
{
	return !m_Deleted;
}

AbstractCollider3D * CollisionHit3D::getCollider()
{
	return m_pCollider;
}
