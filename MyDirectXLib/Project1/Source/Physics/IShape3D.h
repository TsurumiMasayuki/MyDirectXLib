#pragma once
#include "Math\Vec3.h"

class Sphere3D;
class Box3D;

class IShape3D
{
public:
	virtual ~IShape3D() {};

	//当たり判定用関数
	virtual bool isIntersect(const IShape3D& shape3D) const = 0;
	//立方体との当たり判定
	virtual bool isIntersect(const Box3D& box3D) const = 0;
	//球との当たり判定
	virtual bool isIntersect(const Sphere3D & sphere3D) const = 0;

	//押し出し処理用関数
	virtual Vec3 getFixPosition(const IShape3D& shape3D) const = 0;
	//立方体との押し出し処理
	virtual Vec3 getFixPosition(const Box3D& box3D) const = 0;
	//球との押し出し処理
	virtual Vec3 getFixPosition(const Sphere3D & sphere3D)  const = 0;

protected:
	IShape3D() {};
};