#include "Sphere3D.h"
#include <cmath>

Sphere3D::Sphere3D()
	: m_Radius(0.0f)
{
}

void Sphere3D::setPosition(const Vec3 & position)
{
	m_Position = position;
}

const Vec3 & Sphere3D::getPosition() const
{
	return m_Position;
}

void Sphere3D::setRadius(float radius)
{
	m_Radius = radius;
}

float Sphere3D::getRadius() const
{
	return m_Radius;
}

bool Sphere3D::isIntersect(const IShape3D & shape3D) const
{
	return shape3D.isIntersect(*this);
}

bool Sphere3D::isIntersect(const Box3D & box3D) const
{
	return false;
}

bool Sphere3D::isIntersect(const Sphere3D & sphere3D) const
{
	//Œ»İ‚Ì‹——£‚ğŒvZ
	float dist2 = getPosition().sqrDistance(sphere3D.getPosition());
	//Õ“Ë‚Ü‚Å‚ÌÅ’Z‹——£‚ğŒvZ
	float radius2 = std::powf(getRadius() + sphere3D.getRadius(), 2);

	//Œ»İ‚Ì‹——£‚ªÕ“Ë‚Ü‚Å‚ÌÅ’Z‹——£ˆÈ‰º‚È‚çtrue
	return dist2 <= radius2;
}

Vec3 Sphere3D::getFixPosition(const IShape3D & shape3D) const
{
	return shape3D.getFixPosition(*this);
}

Vec3 Sphere3D::getFixPosition(const Box3D & box3D) const
{
	return Vec3();
}

Vec3 Sphere3D::getFixPosition(const Sphere3D & sphere3D) const
{
	Vec3 myPosition = getPosition();
	Vec3 otherPosition = sphere3D.getPosition();

	//Õ“Ë‚µ‚½‹…‘Ì‚©‚çŒ©‚½©g‚Ì•ûŒü‚ğŒvZ
	Vec3 fixDir = (otherPosition - myPosition).normalized();
	//Õ“Ë‚Ü‚Å‚ÌÅ’Z‹——£‚ğŒvZ
	float radius = getRadius() + sphere3D.getRadius();

	return myPosition + fixDir * radius;
}
