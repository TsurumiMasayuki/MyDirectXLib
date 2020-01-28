#pragma once
class AbstractCollider3D;

class CollisionHit3D
{
public:
	CollisionHit3D(AbstractCollider3D* pCollider);
	~CollisionHit3D();

	void onDelete();

	void onAddRef();
	void onRemoveRef();

	bool isAccessable();

	AbstractCollider3D* getCollider();

private:
	AbstractCollider3D* m_pCollider;

	unsigned int m_RefCount;
	bool m_Deleted;
};