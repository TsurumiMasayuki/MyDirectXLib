#pragma once
#include "AbstractCollider3D.h"
#include "Actor\GameObject.h"
#include "Component\Transform.h"
#include "Physics\Sphere3D.h"

class SphereCollider3D
	: public AbstractCollider3D
{
public:
	SphereCollider3D(GameObject* pUser) : AbstractCollider3D(pUser), m_pBox(new Sphere3D()) 
	{};

	~SphereCollider3D() { delete m_pBox; };

	void setRadius(float radius)
	{
		m_pBox->setRadius(radius);
	}

	virtual IShape3D * getShape() override
	{
		m_pBox->setPosition(m_pUser->getTransform()->getPosition());
		return m_pBox;
	}

private:
	Sphere3D* m_pBox;
};