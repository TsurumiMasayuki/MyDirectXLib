#include "Sphere3D.h"
#include "Box3D.h"
#include <cmath>
#include "Math\MathUtility.h"

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
	return box3D.isIntersect(*this);
}

bool Sphere3D::isIntersect(const Sphere3D & sphere3D) const
{
	//現在の距離を計算
	float dist2 = getPosition().sqrDistance(sphere3D.getPosition());
	//衝突までの最短距離を計算
	float radius2 = std::powf(getRadius() + sphere3D.getRadius(), 2);

	//現在の距離が衝突までの最短距離以下ならtrue
	return dist2 <= radius2;
}

Vec3 Sphere3D::getFixPosition(const IShape3D & shape3D) const
{
	return shape3D.getFixPosition(*this);
}

Vec3 Sphere3D::getFixPosition(const Box3D & box3D) const
{
	Vec3 myPosition = getPosition();
	Vec3 otherPosition = box3D.getPosition();

	Vec3 otherSize = box3D.getSize();

	//X, Y, Zでそれぞれ一番近い座標を取る
	Vec3 closestPos(
		MathUtility::clamp(myPosition.x, otherPosition.x - otherSize.x, otherPosition.x + otherSize.x),
		MathUtility::clamp(myPosition.y, otherPosition.y - otherSize.y, otherPosition.y + otherSize.y),
		MathUtility::clamp(myPosition.z, otherPosition.z - otherSize.z, otherPosition.z + otherSize.z)
	);

	//押し出し結果
	Vec3 fixPosLocal = ((closestPos - myPosition).normalized() * getRadius()) - (closestPos - otherPosition);

	return myPosition + fixPosLocal;
}

Vec3 Sphere3D::getFixPosition(const Sphere3D & sphere3D) const
{
	Vec3 myPosition = getPosition();
	Vec3 otherPosition = sphere3D.getPosition();

	//衝突した球体から見た自身の方向を計算
	Vec3 fixDir = (otherPosition - myPosition).normalized();
	//衝突までの最短距離を計算
	float radius = getRadius() + sphere3D.getRadius();

	return myPosition + fixDir * radius;
}
