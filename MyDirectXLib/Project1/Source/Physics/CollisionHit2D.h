#pragma once

class AbstractCollider2D;

class CollisionHit2D
{
public:
	CollisionHit2D(AbstractCollider2D* pCollider);
	~CollisionHit2D();

	void onDelete();

	void onAddRef();
	void onRemoveRef();

	bool isAccessable();

	AbstractCollider2D* getCollider();

private:
	AbstractCollider2D* m_pCollider;

	unsigned int m_RefCount;
	bool m_Deleted;
};