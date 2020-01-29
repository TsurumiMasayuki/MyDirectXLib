#include "Box3D.h"
#include <cmath>
#include "Physics\Sphere3D.h"
#include "Math\MathUtility.h"

Box3D::Box3D()
{
}

bool Box3D::isIntersect(const IShape3D & shape3D) const
{
	return shape3D.isIntersect(*this);
}

bool Box3D::isIntersect(const Box3D & box3D) const
{
	Vec3 myPosition = getPosition();
	Vec3 otherPos = box3D.getPosition();

	Vec3 mySize = getSize();
	Vec3 otherSize = getSize();

	//現在のX,Y,Zそれぞれの距離の絶対値を算出
	const float xDiff = std::fabsf(myPosition.x - otherPos.x);
	const float yDiff = std::fabsf(myPosition.y - otherPos.y);
	const float zDiff = std::fabsf(myPosition.z - otherPos.z);

	//衝突までの最短距離と現在の距離の比較をX,Y,Zそれぞれで行う
	return
		xDiff <= (mySize.x + otherSize.x) &&
		yDiff <= (mySize.y + otherSize.y) &&
		zDiff <= (mySize.z + otherSize.z);
}

bool Box3D::isIntersect(const Sphere3D & sphere3D) const
{
	return false;
}

Vec3 Box3D::getFixPosition(const IShape3D & shape3D) const
{
	return shape3D.getFixPosition(*this);
}

Vec3 Box3D::getFixPosition(const Box3D & box3D) const
{
	Vec3 myPosition = getPosition();
	Vec3 otherPosition = box3D.getPosition();

	Vec3 mySize = getSize();
	Vec3 otherSize = getSize();

	//現在のX,Y,Zそれぞれの距離の差を算出
	const float xDiff = otherPosition.x - myPosition.x;
	const float yDiff = otherPosition.y - myPosition.y;
	const float zDiff = otherPosition.z - myPosition.z;

	//最も距離がある軸
	const float farAxis = std::fmaxf(std::fmaxf(std::fabsf(xDiff), std::fabsf(yDiff)), std::fabsf(zDiff));
	//押し出し結果
	Vec3 fixPosLocal(xDiff, yDiff, zDiff);

	//X方向の押し出し
	if (std::fabsf(xDiff) <= (mySize.x + otherSize.x) &&
		farAxis == std::fabsf(xDiff))
	{
		//Xの最短衝突距離の分押し出す
		fixPosLocal.x = (mySize.x + otherSize.x) * MathUtility::sign(xDiff);
	}

	//Y方向の押し出し
	if (std::fabsf(yDiff) <= (mySize.y + otherSize.y) &&
		farAxis == std::fabsf(yDiff))
	{
		//Yの最短衝突距離の分押し出す
		fixPosLocal.y = (mySize.y + otherSize.y) * MathUtility::sign(yDiff);
	}

	//Z方向の押し出し
	if (std::fabsf(zDiff) <= (mySize.z + otherSize.z) &&
		farAxis == std::fabsf(zDiff))
	{
		//Zの最短衝突距離の分押し出す
		fixPosLocal.z = (mySize.z + otherSize.z) * MathUtility::sign(zDiff);
	}

	return myPosition + fixPosLocal;
}

Vec3 Box3D::getFixPosition(const Sphere3D & sphere3D) const
{
	return sphere3D.getPosition();
}
