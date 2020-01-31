#pragma once
#include "AbstractCollider3D.h"
#include "Actor\GameObject.h"
#include "Component\Transform.h"
#include "Physics\Box3D.h"

//立方体用当たり判定(回転非対応)
class BoxCollider3D
	: public AbstractCollider3D
{
public:
	BoxCollider3D(GameObject* pUser) : AbstractCollider3D(pUser), m_pBox(new Box3D())
	{
	};

	~BoxCollider3D() { delete m_pBox; };

	//サイズ設定
	void setSize(const Vec3& size) { m_pBox->setSize(size); }

	virtual IShape3D * getShape() override
	{
		m_pBox->setPosition(m_pUser->getTransform()->getPosition());
		return m_pBox;
	}

private:
	Box3D* m_pBox;
};