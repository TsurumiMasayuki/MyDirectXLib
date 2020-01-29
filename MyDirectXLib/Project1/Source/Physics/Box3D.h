#pragma once
#include "Physics\IShape3D.h"

class Box3D
	: public IShape3D
{
public:
	Box3D();

	//座標を設定
	void setPosition(const Vec3& position) { m_Position = position; }
	//座標を取得
	const Vec3& getPosition() const { return m_Position; }

	//サイズを設定
	void setSize(const Vec3& size) { m_Size = size; }
	//サイズを取得
	const Vec3& getSize() const { return m_Size; }

	virtual bool isIntersect(const IShape3D & shape3D) const override;
	virtual bool isIntersect(const Box3D & box3D) const override;
	virtual bool isIntersect(const Sphere3D & sphere3D) const override;

	virtual Vec3 getFixPosition(const IShape3D & shape3D) const override;
	virtual Vec3 getFixPosition(const Box3D & box3D) const override;
	virtual Vec3 getFixPosition(const Sphere3D & sphere3D) const override;

private:
	Vec3 m_Position;
	Vec3 m_Size;
};