#pragma once
#include "AbstractCollider3D.h"
#include "Actor\GameObject.h"
#include "Physics\Sphere3D.h"

class SphereCollider3D
	: public AbstractCollider3D
{
public:
	SphereCollider3D(GameObject* pUser) 
		: AbstractCollider3D(pUser),
		m_pSphere(new Sphere3D()) {};
	~SphereCollider3D() { delete m_pSphere; };

	void setRadius(float radius)
	{
		m_Radius = radius;
	}

	virtual IShape3D * getShape() override
	{
		m_pSphere->setPosition(m_pUser->getPosition());
		m_pSphere->setRadius(m_Radius);
		return m_pSphere;
	}

private:
	Sphere3D* m_pSphere;
	float m_Radius;
};