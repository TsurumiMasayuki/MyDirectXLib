#pragma once
#include "Component\AbstractComponent.h"
#include "Math\Vec3.h"

namespace DirectX
{
	struct XMMATRIX;
}

class Transform
	: public AbstractComponent
{
public:
	Transform(GameObject* pUser);
	~Transform();

	virtual void onStart() override {};
	virtual void onUpdate() override {};

	void setPosition(Vec3 position);
	Vec3 getPosition() { return m_Position; }

	void setAngleZ(float angle);
	float getAngleZ() { return m_Angles.z; }

	void setAngles(Vec3 angles);
	Vec3 getAngles() { return m_Angles; }

	void setSize(float size) { m_Size = Vec3(size, size, size); }
	void setSize(Vec3 size) { m_Size = size; }
	Vec3 getSize() { return m_Size; }

	void setLocalPosition(Vec3 position);
	Vec3 getLocalPosition() { return m_LocalPosition; }

	void setLocalAngleZ(float angle);
	float getLocalAngleZ() { return m_LocalAngles.z; }

	void setLocalAngles(Vec3 angles);
	Vec3 getLocalAngles() { return m_LocalAngles; }

	DirectX::XMMATRIX getWorldMatrix();

private:
	void updatePosition();
	void updateAngles();

private:
	Vec3 m_Position;
	Vec3 m_Angles;
	Vec3 m_Size;

	Vec3 m_LocalPosition;
	Vec3 m_LocalAngles;
};