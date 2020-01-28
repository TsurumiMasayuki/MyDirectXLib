#pragma once
#include "IShape3D.h"
#include "Math\Vec3.h"

class Sphere3D
	: public IShape3D
{
public:
	Sphere3D();

	//À•W‚ğİ’è
	void setPosition(const Vec3& position);
	//À•W‚ğæ“¾
	const Vec3& getPosition() const;

	//”¼Œa‚ğİ’è
	void setRadius(float radius);
	//”¼Œa‚ğæ“¾
	float getRadius() const;

	virtual bool isIntersect(const IShape3D& shape3D) const override;
	virtual bool isIntersect(const Box3D & box3D) const override;
	virtual bool isIntersect(const Sphere3D & sphere3D) const override;

	virtual Vec3 getFixPosition(const IShape3D& shape3D) const override;
	virtual Vec3 getFixPosition(const Box3D & box3D) const override;
	virtual Vec3 getFixPosition(const Sphere3D & sphere3D) const override;

private:
	Vec3 m_Position;	//êŠ
	float m_Radius;		//”¼Œa
};